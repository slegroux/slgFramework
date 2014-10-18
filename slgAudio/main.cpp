/**
 * Example rading microphone input and sending it to default system audio output
 */
 
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

#include "Definitions.h"
//#include "MyRtAudio.h"
#include "slgAudio.h"
using namespace std;

// our datetype
#define SAMPLE double
// sample rate
#define MY_SRATE 44100
// number of channels
#define MY_CHANNELS 2
// for convenience
#define MY_PIE 3.14159265358979
#define MY_BUFF_FRAMES = 512;
// corresponding format for RtAudio
#define MY_FORMAT RTAUDIO_FLOAT64


// global for frequency
SAMPLE g_freq = 440.0;
// sample number variable
SAMPLE g_t = 0.0;

unsigned int g_buffSize = 1024;

slgAudio *audio = NULL;

int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData );

//-----------------------------------------------
// name: audioCallback
// desc: read audio in and output to audio out
//-----------------------------------------------
int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;
    
    memset(out, 0, sizeof(SAMPLE)*nFrames*MY_CHANNELS );
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
        out[i*MY_CHANNELS] = ::sin( 2 * MY_PIE * g_freq * g_t / MY_SRATE );
        
        // copy into other channels
        for( int j = 1; j < MY_CHANNELS; ++j )
            out[i*MY_CHANNELS+j] = out[i*MY_CHANNELS];
            
        // increment sample number
        g_t += 1.0;
    }
    return 0;
}



//-----------------------------------------------
// name: initialize
// desc: initialize miscellaneous stuff
//-----------------------------------------------
void initialize()
{    
    //cout<<"Initialize"<<endl;
    //srand( time(NULL) );
}

//-----------------------------------------------
// name: main
// desc: entry point
//-----------------------------------------------
int main ( int argc, char *argv[] )
{   
    initialize();
    //slgAudio audio(2,44100,1024);
    try {
        
        audio = new slgAudio(2, 44100, 1024);

    }
    catch (RtError & err) {
        err.printMessage();
        exit(1);
    }

    audio->info();
    

    try {
        audio->openStream(&audioCallback);
        cout<<"Buffer Size: "<<audio->getBufferSize()<<endl;
        audio->startStream();
        
        
    }
    catch (RtError & err )
    {
        err.printMessage();
    }

    // get input
    char input;
    std::cout << "running... press <enter> to quit"<<endl;
    std::cin.get(input);
    
    try{
        audio->stopStream();
        audio->closeStream();
    } catch (RtError &err) {
        err.printMessage();
    }

    
    return 0;
}