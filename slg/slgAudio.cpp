/*
 *  slgGL.h
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */
 
#include "slgAudio.h"
#include <iostream>
#include <cstdlib>
#include <memory>
using namespace std;

// constructor
slgAudio::slgAudio( unsigned int nChann, unsigned int sr, unsigned int buffSize ){
    m_audio = NULL;
    m_numChannels = nChann;
    m_sampleRate = sr;
    m_bufferSize = buffSize;

    std::cout<<"----------------------------- Audio Settings---------------------------"<<std::endl;
    std::cout<<"nchannels: "<<m_numChannels<<std::endl;
    std::cout<<"sr: "<<m_sampleRate<<std::endl;
    std::cout<<"m_bufferSize: "<<m_bufferSize<<std::endl;
    //std::cout<<"-----------------------------------------------------------------------"<<std::endl;

    try{
        m_audio = new RtAudio();
    }
    catch( RtAudioError & err ) {
        err.printMessage();
        exit(1);
    }

    if( m_audio->getDeviceCount() < 1 )
    {
        // nopes
        std::cout << "no audio devices found!" << std::endl;
        exit(1);
    }
        
    // let RtAudio print messages to stderr.
    m_audio->showWarnings( true );
}

// destructor
slgAudio::~slgAudio(){
    if( m_audio )
    {
        stopStream();
        closeStream();
    }
    delete m_audio;
    m_audio = NULL;
}


// getters & setters

unsigned int slgAudio::buffer_size(){
    return m_bufferSize;
}

void slgAudio::set_input_device(unsigned int input_id){
    m_input_device = input_id;
}

void slgAudio::set_output_device(unsigned int output_id){
     m_output_device = output_id;
}


// RtAudio configuration
void slgAudio::openStream( RtAudioCallback callback, void * userData ){
    if( !callback )
    {
        std::cerr << "No callback provided!" << std::endl;
        exit(1);
    }
    if( m_audio != NULL ){
        stopStream();
        closeStream();
    }
    
    RtAudio::StreamOptions options;
    //options.flags = RTAUDIO_NONINTERLEAVED;
    //options.flags = RTAUDIO_SCHEDULE_REALTIME;
    options.flags = RTAUDIO_MINIMIZE_LATENCY;
    options.priority = 1;

    // set input and output parameters to default
    RtAudio::StreamParameters iParams, oParams;

    //TODO: propose a choice of device not just default
    iParams.deviceId = m_input_device; //m_audio->getDefaultInputDevice();
    iParams.nChannels = 1;
    iParams.firstChannel = 0;
    oParams.deviceId = m_output_device; //m_audio->getDefaultOutputDevice();
    oParams.nChannels = 2;
    oParams.firstChannel = 0;
    
    RtAudioFormat sample_format = ( sizeof(SAMPLE) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    //open stream
    //!!! RTAUDIO_FLOAT32 and not 64...
    try {
        m_audio->openStream( &oParams, &iParams, sample_format, m_sampleRate, &m_bufferSize, callback, userData, &options);
    } 
    catch ( RtAudioError& e ) {
        try { // again
            std::cout<<"hack!"<<std::endl;
            // HACK: bump the oparams device id (on some systems, default in/out devices differ)
            oParams.deviceId++;
            // try to open stream
            m_audio->openStream( &oParams, &iParams, sample_format,
                                m_sampleRate, &m_bufferSize, callback, userData );
        } 
        catch( RtAudioError & e ) {
            // error message
            std::cerr << "[slgAudio]: cannot initialize real-time audio I/O..." << std::endl;
            std::cerr << "[slgAudio]: | - " << e.getMessage() << std::endl;
            // clean up
            delete m_audio;
            m_audio = NULL;
            // done
        }
    }
}

void slgAudio::test(){
    std::cout<<"------------------------------ Test ------------------------------------"<<std::endl;
    std::cout << "Number of audio device found: " << m_audio->getDeviceCount() << std::endl;
}

void print_vector(std::vector<unsigned int> const &input)
{
    for (auto const& i: input){
        std::cout << i <<" ";
    }
}
void slgAudio::info(){
    unsigned int devices = m_audio->getDeviceCount();
    RtAudio::DeviceInfo info;
    
    std::cout<<"----------------------------- Devices INFO-----------------------"<<std::endl;
    std::cout<<"RtAudio Version"<<RtAudio::getVersion() << std::endl;
    std::cout<<"default input: "<<m_audio->getDefaultInputDevice()<<std::endl;
    std::cout<<"default output: "<<m_audio->getDefaultOutputDevice()<<std::endl;
    
    for (int i=0; i<devices; i++){    
        info = m_audio->getDeviceInfo(i);
        if (info.probed == true){
            std::cout<<"----------------------------- Device #"<<i<<" INFO-----------------------"<<std::endl;
            if (info.isDefaultInput)
                std::cout << "Default Input"<<std::endl;
            if (info.isDefaultOutput)
                std::cout << "Default Output"<<std::endl;      
            std::cout << "Name: " << info.name << '\n';
            std::cout << "Max Input Channels = " << info.inputChannels << '\n';
            std::cout << "Max Output Channels = " << info.outputChannels << '\n';
            std::cout << "Max Duplex Channels = " << info.duplexChannels << '\n';
            std::cout << "Supported Sampling rates: ";
            print_vector(info.sampleRates);
            cout<<endl;            
        }
    }
}

// start audio stream
void slgAudio::startStream(){
    try{
        m_audio->startStream();        
        // RtAudio functionality for reporting latency.
        std::cout<< "-------- Real-time latency --------"<<std::endl;
        std::cout << "stream latency: " << m_audio->getStreamLatency() << " frames" << std::endl;
    }
    catch( RtAudioError & err ){
        // error message
        std::cerr << "[slgAudio]: cannot start real-time audio I/O..." << std::endl;
        std::cerr << "[slgAudio]: | - " << err.getMessage() << std::endl;
        //err.printMessage();
    }
}

// stop audio stream
void slgAudio::stopStream(){
    if( m_audio )
    {
        if ( m_audio->isStreamRunning() ) 
            m_audio->stopStream();
    }
}

void slgAudio::closeStream(){
    if (m_audio){
        if ( m_audio->isStreamOpen() )
            m_audio->closeStream();
    }
}
