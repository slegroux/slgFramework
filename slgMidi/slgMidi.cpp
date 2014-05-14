#include "slgMidi.h"
#include <iostream>

slgMidi::slgMidi(){
	m_midiin = NULL;
	m_midiout = NULL;
	//unsigned char at least 0-255 range
	// unsigned char mess[] = {0,0,0};
	// m_message(mess,mess+sizeof(mess)/sizeof(unsigned char))
	m_message.push_back(0);
	m_message.push_back(0);
	m_message.push_back(0);

}

slgMidi::~slgMidi(){
	if (m_midiin)
	{
		delete m_midiin;
	}
	if (m_midiout)
	{
		delete m_midiout;
	}

}

void slgMidi::setup(void *userData){

	try{
		m_midiin = new RtMidiIn();
	}
	catch(RtMidiError &error){
		error.printMessage();
		exit(1);
	}

	try{
		m_midiout = new RtMidiOut();
	}
	catch(RtMidiError &error){
		error.printMessage();
		exit(1);
	}

	// Check available ports.
    unsigned int nPorts = m_midiin->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No ports available!\n";
        //goto cleanup;
    }
    // Don't ignore sysex, timing, or active sensing messages.
    m_midiin->ignoreTypes( false, false, false );
}

void slgMidi::start(RtMidiIn::RtMidiCallback callback){

	if(!callback){
		std::cerr<<"No callback provided! "<<std::endl;
		exit(1);
	}

	m_midiin->openPort( 0 );
    // Set callback function.  This should be done immediately after
    // opening the port to avoid having incoming messages written to the
    // queue.
    m_midiin->setCallback( callback );

    m_midiout->openPort(0);

}

void slgMidi::send(std::vector<unsigned char> message){
	std::cout<<"send: "<<message[0]<<std::endl;
	m_midiout->sendMessage(&message);
}

void slgMidi::info(){
	// check input
	unsigned int nPorts = m_midiin->getPortCount();
	std::cout<<"-------- Default input --------"<<std::endl;
	std::cout << "There are " << nPorts << " MIDI input sources available.\n";
	std::string portName;
	portName = m_midiin->getPortName(0);
	std::cout << "Input Port #" << 0 << ": " << portName << '\n';
    // Check outputs.
	nPorts = m_midiout->getPortCount();
	std::cout<<"-------- Default output --------"<<std::endl;
	std::cout << "There are " << nPorts << " MIDI output ports available.\n";
	portName = m_midiout->getPortName(0);
	std::cout << "Output Port #" << 0 << ": " << portName << '\n';
	std::cout<<"--------"<<std::endl;
}