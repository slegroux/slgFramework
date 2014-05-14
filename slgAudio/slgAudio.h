/**
 * process audio
 */

#ifndef __SLG_AUDIO_H__
#define __SLG_AUDIO_H__

#include "Definitions.h"
#include "RtAudio/RtAudio.h"


class slgAudio {

public:

    slgAudio( unsigned int nChann = 2, float sr = MY_SRATE, 
             unsigned int buffSize = 512 );
    ~slgAudio();
    
public:
    /**
     * @brief setup audio
     * @details use callback function
     */
    void setup( RtAudioCallback callback, void * userData = NULL );
    /**
     * @brief start audio stream
     */
    void start();
    /**
     * @brief stop audio stream
     */
    void stop();
    /**
     * @brief get buffer size
     * @return unsigned int for size of buffer
     */
    unsigned int bufferSize() { return m_bufferSize; };
    /**
     * @brief info
     * @details give infor about open audio devices
     */
    void info();
    
private:
    RtAudio * m_audio;
    unsigned int m_numChannels;
    float m_sampleRate;
    unsigned int m_bufferSize;
};

#endif
