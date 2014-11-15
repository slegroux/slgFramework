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

// constructor
slgAudio::slgAudio( unsigned int nChann, unsigned int sr, unsigned int buffSize )
{
    m_audio = NULL;
    m_numChannels = nChann;
    m_sampleRate = sr;
    m_bufferSize = buffSize;

    std::cout<<"--- Audio Settings---"<<std::endl;
    std::cout<<"nchannels: "<<m_numChannels<<std::endl;
    std::cout<<"sr: "<<m_sampleRate<<std::endl;
    std::cout<<"m_bufferSize: "<<m_bufferSize<<std::endl;

    try
    {
        m_audio = new RtAudio();
    }
    catch( RtError & err ) {
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
slgAudio::~slgAudio()
{
    /*if( m_audio )
    {
        stop();
        close();
    }*/
    delete m_audio;
    m_audio = NULL;
}


// RtAudio configuration
void slgAudio::openStream( RtAudioCallback callback, void * userData )
{
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
    options.flags = RTAUDIO_SCHEDULE_REALTIME;
    options.priority = 1;

    // set input and output parameters to default
    RtAudio::StreamParameters iParams, oParams;

    //TODO: propose a choice of device not just default
    iParams.deviceId = m_audio->getDefaultInputDevice();
    iParams.nChannels = 2;
    iParams.firstChannel = 0;
    oParams.deviceId = m_audio->getDefaultOutputDevice();
    oParams.nChannels = 2;
    oParams.firstChannel = 0;
    
    //open stream
    //!!! RTAUDIO_FLOAT32 and not 64...
    m_audio->openStream( &oParams, &iParams, RTAUDIO_FLOAT32, m_sampleRate, &m_bufferSize, callback, userData, &options); 

}

void slgAudio::info(){
    RtAudio *audioTemp = NULL;
    audioTemp = new RtAudio();
    unsigned int devices = audioTemp->getDeviceCount();
    RtAudio::DeviceInfo info;
    
    for (int i=0;i<devices;i++){
        info = audioTemp->getDeviceInfo(i);
        // std::cout<<"default input: "<<m_audio->getDefaultInputDevice()<<std::endl;
        // std::cout<<"default output: "<<m_audio->getDefaultOutputDevice()<<std::endl;
        if (info.probed ==true){
            std::cout<<"----------------------------- Device "<<i<<" ---------------------------"<<std::endl;
            if (info.isDefaultInput)
                std::cout << "--Default Input"<<std::endl;
            if (info.isDefaultOutput)
                std::cout << "--Default Output"<<std::endl;      
            std::cout << "Name = " << info.name << '\n';
            std::cout << "Max Input Channels = " << info.inputChannels << '\n';
            std::cout << "Max Output Channels = " << info.outputChannels << '\n';
            std::cout << "Max Duplex Channels = " << info.duplexChannels << '\n';
        }
    }
    delete audioTemp;
    audioTemp = NULL;
}

// start audio stream
void slgAudio::startStream()
{
    try
    {
         m_audio->startStream();        
        // RtAudio functionality for reporting latency.
        std::cout<< "-------- Real-time latency --------"<<std::endl;
        std::cout << "stream latency: " << m_audio->getStreamLatency() << " frames" << std::endl;
    }
    catch( RtError & err )
    {
        err.printMessage();
    }
}

// stop audio stream
void slgAudio::stopStream()
{
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
