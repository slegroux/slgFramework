#include <stdlib.h>
#include <iostream>
#include "RtMidi.h"
#include "RtAudio.h"
#include "slgMidi.h"
#include "slgAudio.h"
#include "slgFluidSynth.h"
#include <unistd.h>

//!! fluidsynth returns float so will only work if SAMPLE type is defined as float 
// in the Definitions.h file: #define SAMPLE float

#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

using namespace std;

//global variables
slgFluidSynth *g_synth = NULL;
slgAudio *g_audio = NULL;
slgMidi *g_midi = NULL;

unsigned int g_t =0;
SAMPLE g_freq = 440.0;

int audioCallback( void *outputBuffer, void *inputBuffer, unsigned int nFrames,
        double streamTime, RtAudioStreamStatus status, void *userData ){

    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
    SAMPLE * out = (SAMPLE *)outputBuffer;

    g_synth->Render( out, nFrames );
    
    // SAMPLE * buffy = (SAMPLE *)outputBuffer;
    
    // for( int i = 0; i < nBufferFrames; i++ )
    // {
    //     SAMPLE temp = .5*(buffy[i*2] + buffy[i*2 + 1]);
    //     //temp = g_rev->tick(temp);
        
    //     buffy[i*2] = buffy[i*2 + 1] = 2.0*temp;
    // }

    /*for( int i = 0; i < nFrames; ++i )
    {
        // generate signal
        out[i*kNumChannels] = ::sin( 2 * M_PI * g_freq * g_t / kSampleRate );
        
        // copy into other channels
        for( int j = 1; j < kNumChannels; ++j )
            out[i*kNumChannels+j] = out[i*kNumChannels];
            
        // increment sample number
        g_t += 1.0;
    }*/
        
    return 0;
}

// midi callback
void midiCallback( double deltatime, std::vector< unsigned char > *message, void *userData ){
    unsigned int nBytes = message->size();
    // for ( unsigned int i=0; i<nBytes; i++ )
    //     std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    // if ( nBytes > 0 )
    //     std::cout << "stamp = " << deltatime << std::endl;
    
    int pitch = (int)message->at(1);
    int vol = (int)message->at(2);
                
    // only care about 3-byte messages
    if( nBytes == 3 )
    {
        // look at first byte in message
        switch( (int)message->at(0) )
        {
            case 144:{
                //NOTE ON
                cerr << "NOTEON: "<<endl; //<< (int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                g_synth->NoteOn(0, pitch, vol);
                std::cout << "Pitch:" << pitch << " Volume:" << vol << std::endl;
                break;
            }
                
            case 128:{
                //NOTE OFF
                cout << "NOTEOFF: " << endl;//(int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                g_synth->NoteOff(0, pitch);
                break;
            }
            default:
                cerr << "OTHER!: " << (int)message->at(0) << ":" << (int)message->at(1) << ":" << (int)message->at(2) << endl;
                break;
        }
    }
}


// entry point
int main(){
    
    // Audio
    g_audio = new slgAudio(kNumChannels, kSampleRate, kFrameSize);
    g_audio->info();
    g_audio->openStream(&audioCallback);
    

    //fluidsynth
    g_synth = new slgFluidSynth(kSampleRate);
    //g_synth->Load("data/FluidR3_GM.sf2");
    g_synth->Load("data/rocking8m11e.sf2");
    g_synth->ProgramChange(0,80);

    g_audio->startStream();
    // MIDI
    g_midi = new slgMidi();
    // check # of inputs and outputs
    g_midi->Info();
    // choose midi ports when several options and start CB
    g_midi->set_input_port(0);
    g_midi->Start(&midiCallback);

    // send MIDI messages
    //unsigned char at least 0-255 range
    /*unsigned char mess[] = {144,64,90};
    std::vector<unsigned char> message(mess,mess+sizeof(mess)/sizeof(unsigned char));    
    midi.sendMessage(message);
    SLEEP(2000);
    message[0] = 144;
    message[1] = 64;
    message[2] = 100;
    midi.sendMessage(message);
    SLEEP(1000);
    message[0] = 144;
    message[1] = 64;
    message[2] = 100;
    midi.sendMessage(message);
    SLEEP(1000);
    message[0] = 144;
    message[1] = 65;
    message[2] = 100;
    midi.sendMessage(message);*/
    
    /*std::cout << "reading MIDI input/ sending MIDI output... press <enter> to quit.\n";
    char input;
    std::cin.get(input);*/
    int input;
    int pitch = 0;
    
    std::cout << "\nPlaying ... press CTRL-C to quit.\n";
    std::cout << "\Enter number to change GM instrument.\n";
    while(true)
    {
        std::cin >> input;
        
        if( (input >  0 ) && (input < 128) )
        {
            std::cout << "program change: " << input << std::endl;
            g_synth->ProgramChange(0, input);
        }
    }

    /*do{
        cerr << "enter pitch number and hit ENTER (0 to quit): ";
        cin >> pitch;
        g_synth->NoteOn(0,pitch,127);
    }while(pitch>0);*/

    g_audio->stopStream();
    g_audio->closeStream();

    return 0;
}
