/*
 * slgMidi.cpp
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */

#include "slgMidi.h"
#include <iostream>

slgMidi::slgMidi(){
	m_midiin = NULL;
	m_midiout = NULL;
	Setup();
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
	printf("cleanup slgMidi");
}

void slgMidi::Setup(){

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
    /*unsigned int nPorts = m_midiin->getPortCount();

    if ( nPorts == 0 ) {
        std::cout << "No input ports available! plug input midi device.\n";
        //goto cleanup;
    }*/
    // Don't ignore sysex, timing, or active sensing messages.
    m_midiin->ignoreTypes( false, false, false );
}

void slgMidi::set_input_port(unsigned int input_port){
	m_midiin->openPort(input_port);
	cout << "\nOpening Midi Input Port: " << m_midiin->getPortName() << endl;
}

void slgMidi::set_output_port(unsigned int output_port){
	m_midiout->openPort(output_port);
	cout << "\nOpening Midi Output Port: " << m_midiout->getPortName() << endl;
}

void slgMidi::Start(RtMidiIn::RtMidiCallback callback){

	if(!callback){
		std::cerr<<"No callback provided! "<<std::endl;
		exit(1);
	}

	/*
	std::string portName;
    unsigned int i = 0;
    unsigned int nPorts = m_midiout->getPortCount();

	if ( nPorts == 1 ) 
    {
        cout << "\nOpening " << m_midiout->getPortName() << endl;
    }
    else 
    {
        do 
        {
            cout << "\nChoose a port number: ";
            cin >> i;
            cin.ignore(256,'\n');

        } while ( i >= nPorts );
    }

    std::cout << "\n";
	m_midiout->openPort( i );*/

    // Set callback function.  This should be done immediately after
    // opening the port to avoid having incoming messages written to the
    // queue.
    m_midiin->setCallback( callback );
}

void slgMidi::set_message(std::vector<unsigned char> message){
	m_message = message;
}

void slgMidi::SendMessage(std::vector<unsigned char> message){
	std::cout<<"send: "<<(int)message[0]<<' '<<(int)message[1]<<' '<<(int)message[2]<<std::endl;
	m_midiout->sendMessage(&message);
}

void slgMidi::Info(){
	// check input
	unsigned int nPorts = m_midiin->getPortCount();
	std::cout<<"-------- MIDI Inputs --------"<<std::endl;
	std::cout << "There are " << nPorts << " MIDI input sources available.\n";
	std::string portName;
	
	for (int i=0;i<nPorts;++i){
		portName = m_midiin->getPortName(i);
		std::cout << "Input Port #" << i << ": " << portName << '\n';
	}
    // Check outputs.
	nPorts = m_midiout->getPortCount();
	std::cout<<"-------- MIDI outputs --------"<<std::endl;
	std::cout << "There are " << nPorts << " MIDI output ports available.\n";
	for (int i=0;i<nPorts;++i){
		portName = m_midiout->getPortName(i);
		std::cout << "Output Port #" << i << ": " << portName << '\n';
	}
}