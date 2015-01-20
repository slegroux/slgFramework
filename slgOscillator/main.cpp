/**
 * 
 */
 
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "Definitions.h"
#include "slgAudio.h"
#include "slgOscillator.h"

using namespace std;
// defines and consts

struct callback_data{
    slgOscillator oscillator;
} my_callback_data;

int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData ){

    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;
    callback_data* data = (callback_data*) userData;
    
    // fill
    for( int i = 0; i < nFrames; ++i ){
        
        // generate signal
        out[i*kNumChannels] = my_callback_data.oscillator.render();
        
        // copy into other channels
        for( int j = 1; j < kNumChannels; ++j )
            out[i*kNumChannels+j] = out[i*kNumChannels];
    }

    return 0;
}


int main ( int argc, char *argv[] ){   

    slgAudio audio(kNumChannels,kSampleRate,kFrameSize);  
    //audio.info();
    my_callback_data.oscillator.set_frequency(520.0);
    my_callback_data.oscillator.set_mode(kSin);
    
    audio.openStream(&audioCallback,&my_callback_data);
//    audio.getBufferSize();
    audio.startStream();
    
    // get input
    char input;
    std::cout << "running... press <enter> to quit"<<endl;
    std::cin.get(input);
    
    audio.stopStream();
    audio.closeStream();

    return 0;
}