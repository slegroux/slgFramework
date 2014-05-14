#ifndef __SLGAUDIO_H__
#define __SLGAUDIO_H__

#include "Definitions.h"
#include "RtAudio/RtAudio.h"

class slgAudio {

public:
    slgAudio( unsigned int nChann = 2, float sr = MY_SRATE, 
             unsigned int buffSize = 512 );
    ~slgAudio();
    
public:
    void setup( RtAudioCallback callback, void * userData = NULL );
    void start();
    void stop();
    unsigned int bufferSize() { return m_bufferSize; };
    void info();
    
private:
    RtAudio * m_audio;
    unsigned int m_numChannels;
    float m_sampleRate;
    unsigned int m_bufferSize;
};

#endif
