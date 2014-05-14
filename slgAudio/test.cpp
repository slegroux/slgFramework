/**
 * Example rading microphone input and sending it to default system audio output
 */
 
#include <iostream>
#include <string>
#include <math.h>

#include "Definitions.h"
#include "slgAudio.h"
using namespace std;

unsigned int g_numChannels = NUM_CHANNS;


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
    
    
    for(size_t i = 0; i < bufferSize; ++i)
    {
        out[i*g_numChannels] = in[i*g_numChannels];
           
        for(size_t j = 1; j < g_numChannels; ++j)
        {
            out[i*g_numChannels+j] = out[i*g_numChannels];
        }
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