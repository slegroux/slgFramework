/*
 *  slgGL.h
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */

#ifndef __SLG_AUDIO_H__
#define __SLG_AUDIO_H__

#include "Definitions.h"
#include "RtAudio.h"


class slgAudio {

public:

    slgAudio( unsigned int nChann = 2, unsigned int samplingRate = 44100.0, unsigned int buffSize = 512 );
    ~slgAudio();
    
public:
    /**
     * @brief setup audio
     * @details use callback function
     */
    void openStream( RtAudioCallback callback, void * userData = NULL );

    /**
     * @brief start audio stream
     */
    void startStream();
    /**
     * @brief stop audio stream
     */
    void stopStream();
    /**
     * @brief close audio stream
     */
    
    void closeStream();
    /**
     * @brief get buffer size
     * @return unsigned int for size of buffer
     */
    unsigned int getBufferSize() { return m_bufferSize; };
    /**
     * @brief info
     * @details give infor about open audio devices
     */
    void info();
    
private:
    RtAudio * m_audio;
    unsigned int m_numChannels;
    unsigned int m_sampleRate;
    unsigned int m_bufferSize;
};

#endif
