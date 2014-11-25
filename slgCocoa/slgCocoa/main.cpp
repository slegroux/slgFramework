//
//  main.cpp
//  slgCocoa
//
//  Created by Sylvain Le Groux on 11/16/14.
//  Copyright (c) 2014 Sylvain Le Groux. All rights reserved.
//

#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "Definitions.h"
#include "slgAudio.h"

using namespace std;
// defines and consts
//const unsigned int g_buffSize = 1024;

// global
SAMPLE g_freq = 440.0;
SAMPLE g_t = 0.0;

int audioCallback( void * outputBuffer, void * inputBuffer,
                  unsigned int nFrames, double streamTime,
                  RtAudioStreamStatus status, void * userData )
{
    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;
    //SAMPLE * in = (SAMPLE *)inputBuffer;
    
    //memset(out, 0, sizeof(SAMPLE)*nFrames*kNumChannels );
    //memset(in, 0, sizeof(SAMPLE)*nFrames*MY_CHANNELS );
    
    /*for(size_t i = 0; i < nFrames; ++i)
     {
     // If 2 channels per frame
     // left channel with samples 0*2, 1*2, 2*2 ... 0,2,4
     out[i*MY_CHANNELS] = in[i*MY_CHANNELS];
     
     // right channel with samples 0*2+1, 1*2+1, ... 1,3,5
     for(size_t j = 1; j < MY_CHANNELS; ++j)
     {
     out[i*MY_CHANNELS+j] = out[i*MY_CHANNELS];
     }
     }*/
    
    // fill
    for( int i = 0; i < nFrames; ++i )
    {
        // generate signal
        out[i*kNumChannels] = ::sin( 2 * M_PI * g_freq * g_t / kSampleRate );
        
        // copy into other channels
        for( int j = 1; j < kNumChannels; ++j )
            out[i*kNumChannels+j] = out[i*kNumChannels];
        
        // increment sample number
        g_t += 1.0;
    }
    return 0;
}


int main ( int argc, char *argv[] ){
    
    slgAudio audio(kNumChannels,kSampleRate,kFrameSize);
    audio.info();
    audio.openStream(&audioCallback);
    audio.getBufferSize();
    audio.startStream();
    
    // get input
    char input;
    std::cout << "running... press <enter> to quit"<<endl;
    std::cin.get(input);
    
    audio.stopStream();
    audio.closeStream();
    
    return 0;
}