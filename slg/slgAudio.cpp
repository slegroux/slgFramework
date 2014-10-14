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
slgAudio::slgAudio( unsigned int nChann, float sr, unsigned int buffSize )
{
    m_audio = NULL;
    m_numChannels = nChann;
    m_sampleRate = sr;
    m_bufferSize = buffSize;
}

// destructor
slgAudio::~slgAudio()
{
    if( m_audio )
    {
        stop();
        delete m_audio;
    }
}

// RtAudio configuration
void slgAudio::setup( RtAudioCallback callback, void * userData )
{
    if( !callback )
    {
        std::cerr << "No callback provided!" << std::endl;
        exit(1);
    }
        
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

    // set input and output parameters
    RtAudio::StreamParameters iParams, oParams;
    iParams.deviceId = m_audio->getDefaultInputDevice();
    iParams.nChannels = m_numChannels;
    iParams.firstChannel = 0;
    oParams.deviceId = m_audio->getDefaultOutputDevice();
    oParams.nChannels = m_numChannels;
    oParams.firstChannel = 0;
    
    // set the callback and start stream
    try
    {
        m_audio->openStream( &oParams, 
                             &iParams, 
                             RTAUDIO_FLOAT64, 
                             m_sampleRate, 
                             &m_bufferSize, 
                             callback, 
                             userData);
        
        std::cerr << "Buffer size defined by RtAudio: " << m_bufferSize << std::endl;
    }
    catch( RtError & err )
    {
        err.printMessage();
        exit(1);
    }
    
}

void slgAudio::info(){
    
    RtAudio::DeviceInfo info;
    for (int i=0;i<2;i++){
        info = m_audio->getDeviceInfo(i);
        // std::cout<<"default input: "<<m_audio->getDefaultInputDevice()<<std::endl;
        // std::cout<<"default output: "<<m_audio->getDefaultOutputDevice()<<std::endl;
        std::cout<<"-------- Default Input/Output --------"<<std::endl;
        std::cout << "Device Name = " << info.name << '\n';
        std::cout << "Output Channels = " << info.outputChannels << '\n';
        std::cout << "Input Channels = " << info.inputChannels << '\n';
        std::cout << "Duplex Channels = " << info.duplexChannels << '\n';
    }
}

// start audio stream
void slgAudio::start()
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
        exit(1);
    }
}

// stop audio stream
void slgAudio::stop()
{
    if( m_audio )
    {
        if ( m_audio->isStreamRunning() ) m_audio->stopStream();
        if ( m_audio->isStreamOpen() ) m_audio->closeStream();
    }
}
