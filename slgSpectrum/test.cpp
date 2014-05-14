#include <iostream>
#include <string>
#include <math.h>

#include "Definitions.h"
#include "slgAudio.h"
#include "slgSpectrum.h"
#define BUFFER_SIZE 1024

using namespace std;

unsigned int g_numChannels = NUM_CHANNS;
slgSpectrum g_spectrum;

//-----------------------------------------------
// name: audioCallback
// desc: read audio in and output to audio out
//-----------------------------------------------
int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int bufferSize, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;

    // casting to float
    float *myIn;
    myIn = new float[bufferSize];
    for (int i=0;i<bufferSize;++i){
        myIn[i] = (float) in[i];
    }

    float *my_spectrum = new float[BUFFER_SIZE/2];

    my_spectrum = g_spectrum.getSpectrum(myIn,bufferSize);
    cout<<"First bin of spectrum: "<<my_spectrum[0]<<endl;
/*
    for(size_t i = 0; i < bufferSize; ++i)
    {
        out[i*g_numChannels] = in[i*g_numChannels];
           
        for(size_t j = 1; j < g_numChannels; ++j)
        {
            out[i*g_numChannels+j] = out[i*g_numChannels];
        }
    }*/
    
    return 0;
}


//-----------------------------------------------
// name: initialize
// desc: initialize miscellaneous stuff
//-----------------------------------------------
void initialize()
{    
    g_spectrum.init(BUFFER_SIZE);
}

//-----------------------------------------------
// name: main
// desc: entry point
//-----------------------------------------------
int main ( int argc, char *argv[] )
{    
    // init
    initialize();
    
    // config audio 
    slgAudio audio( g_numChannels, MY_SRATE, BUFFER_SIZE );
    audio.setup( &audioCallback, NULL );

    // info about default input/output devices
    audio.info();

    // start audio
    audio.start();

    // while not quitting
    std::cout << "Processing audio... press <enter> to quit.\n";
    char input;
    std::cin.get(input);
        
    // stop before quiting
    audio.stop();
    
    return 0;
}