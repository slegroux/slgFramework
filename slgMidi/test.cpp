#include <stdlib.h>
#include <iostream>
using namespace std;
#include "RtMidi/RtMidi.h"
#include "slgMidi.h"

// midi callback
void midiCallback( double deltatime, std::vector< unsigned char > *message, void *userData ){
    unsigned int nBytes = message->size();
    for ( unsigned int i=0; i<nBytes; i++ )
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if ( nBytes > 0 )
        std::cout << "stamp = " << deltatime << std::endl;


    // only care about 3-byte messages
    if( nBytes == 3 )
    {
        // look at first byte in message
        switch( (int)message->at(0) )
        {
            case 144: // note on
                cerr << "NOTEON: " << (int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                break;
                
            case 128:
                cout << "NOTEOFF: " << (int)message->at(0) << ":" << (int)message->at(1) << " v: " << (int)message->at(2) << endl;
                break;
            
            default:
                cerr << "OTHER!: " << (int)message->at(0) << ":" << (int)message->at(1) << ":" << (int)message->at(2) << endl;
                break;
        }
    }
}


// entry point
int main(){

    slgMidi midi;
    midi.setup(NULL);
    midi.info();
    midi.start(&midiCallback);

    //unsigned char at least 0-255 range
    unsigned char mess[] = {144,64,90};
    std::vector<unsigned char> message(mess,mess+sizeof(mess)/sizeof(unsigned char));    
    midi.send(message);


    message[0] = 176;
    message[1] = 7;
    message[2] = 100;
    midi.send(message);

    std::cout << "reading MIDI input/ sending MIDI output... press <enter> to quit.\n";
    char input;
    std::cin.get(input);

}
