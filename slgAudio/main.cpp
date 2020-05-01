/**
 * Example reading microphone input and sending it to default system audio output
 */
 
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <getopt.h>
#include "Definitions.h"
#include "slgAudio.h"

using namespace std;
// defines and consts
const unsigned int g_buffSize = 1024;

// global
SAMPLE g_freq = 440.0;
int g_t = 0;
auto kNumChannels = 2;
unsigned int kSampleRate = 44100;
auto kFrameSize = 512;

int sine_callback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;
    
    memset(out, 0, sizeof(SAMPLE)*nFrames*kNumChannels);
    //memset(in, 0, sizeof(SAMPLE)*nFrames*MY_CHANNELS );
    
    // fill
    for( int i = 0; i < nFrames; ++i )
    {
        // generate signal 
        // left
        out[i*kNumChannels] = 0.8 * ::sin( 2 * M_PI * g_freq * g_t / kSampleRate );
        // right 
        out[i*kNumChannels + 1] = out[i*kNumChannels];
                
        // increment sample number
        g_t += 1;
    }
    return 0;
}

int mic_callback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;
    
    memset(out, 0, sizeof(SAMPLE)*nFrames*kNumChannels);
    //memset(in, 0, sizeof(SAMPLE)*nFrames*kNumChannels);
        
    // fill
    for( int i = 0; i < nFrames; ++i )
    {
        // generate signal
        out[i*kNumChannels] = 0.9 * in[i*kNumChannels];
        out[i*kNumChannels + 1] = out[i*kNumChannels];
    }
    return 0;
}

int main ( int argc, char *argv[] ){   
    std::cout << "Running program: " << argv[0] << std::endl;
    slgAudio audio(kNumChannels, kSampleRate, kFrameSize);    
    audio.info();
    //audio.test();
    std::cout << "Buffer size: " << audio.buffer_size()<<std::endl;
    // audio.set_input_device(0);
    // audio.set_output_device(1);
    int opt, s, r;
    // while ((opt = getopt(argc, argv,"s:r:")) != -1)
    //     switch(opt){
    //         case 's':   s = 1; 
    //                     std::cout << "sine wave" << std::endl;
    //                     std::cout << "optarg: " << optarg << std::endl;
    //                     audio.openStream(&sine_callback);
    //                     break;
    //         case 'r':   r = 1;
    //                     cout<<"record mic"<<endl;
    //                     //audio.openStream(&mic_callback);
    //                     break;
    //         default:    cout<<endl;
    //                     abort();
    //     }

   
    audio.openStream(&sine_callback);
    audio.startStream();
    
    // get input
    char input;
    std::cout << "running... press <enter> to quit"<<endl;
    std::cin.get(input);
    
    audio.stopStream();
    audio.closeStream();
    

    return 0;
}