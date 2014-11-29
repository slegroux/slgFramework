#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>

#include "Definitions.h"
#include "slgAudio.h"
#include "Synthesizer.h"
#include "slgMidi.h"

using namespace std;

const float g_freq = 220;
float g_t = 0;
Synthesizer g_instrument;
slgMidi g_midi;

int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData ){

    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;
    SAMPLE * in = (SAMPLE *)inputBuffer;
    
    //memset(out, 0, sizeof(SAMPLE)*nFrames*kNumChannels );
    
    for (int i = 0;i<nFrames;++i){
        out[i*kNumChannels] = g_instrument.Tick();
        for (int j = 1; j < kNumChannels ; ++j){
            out[i*kNumChannels+j] = out[i*kNumChannels];
        }
    }
    
    return 0;
}

void midiCallback( double deltatime, std::vector< unsigned char > *message, void *userData ){
    unsigned int nBytes = message->size();
    int pitch = (int)message->at(1);
    int vol = (int)message->at(2);
    
    if( nBytes == 3 )
    {
        // look at first byte in message
        switch( (int)message->at(0) )
        {
            case 144: // note on
                if (message->at(2)!=0){
                    cerr << "NOTEON: " << (int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                    g_instrument.NoteOn( 440*pow(2.0, (pitch-69)/12.0f) );
                }
                if (message->at(2)==0){
                    cout << "NOTEOFF: " << (int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                    g_instrument.NoteOff();
                }
                break;
                
            case 128:
                cout << "NOTEOFF: " << (int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                g_instrument.NoteOff();
                break;
            
            default:
                cerr << "OTHER!: " << (int)message->at(0) << ":" << (int)message->at(1) << ":" << (int)message->at(2) << endl;
                break;
        }
    }
}


int main ( int argc, char *argv[] ){

    // MIDI
    // check # of inputs and outputs
    g_midi.Info();
    g_midi.set_input_port(0);
    //g_midi.set_output_port(0);
    // choose midi ports when several options and start CB
    g_midi.Start(&midiCallback);


    // STK "globals"
    stk::Stk::setSampleRate(kSampleRate);
    // some Stk classes read data from files (included in the Stk source). 
    // Use this method to tell the app where to look for those files
    stk::Stk::setRawwavePath("rawwaves/");
    
    // seed random number generator
    srand(time(NULL));

    slgAudio audio(kNumChannels,kSampleRate,kFrameSize);
    
    unsigned int harms = 10;
    g_instrument.SetHarmonics(harms);
    // "scale" 
    float scale[5] = {0, 2, 5, 7, 9};

    audio.info();
    audio.openStream(&audioCallback);
    audio.startStream();
    
    // wait for user input
    do {
        char c;
        std::cin >> c;
        if (c == 'u') // increase harmonics
            g_instrument.SetHarmonics( ++harms );
        else if (c == 'd')  // decrease harmonics
            g_instrument.SetHarmonics( --harms );
        else if (c == 'p')  // play a note
            g_instrument.NoteOn( 440.0 * pow(2.0, scale[rand() % 5]/12.0f) );
        else if (c == 's')  // stops the playing note
            g_instrument.NoteOff();
        else if (c == 'q')
            break;
    } while( true );

    audio.stopStream();
    audio.closeStream();

    return 0;
}