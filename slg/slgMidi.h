/*
 *  slgGL.h
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */

#ifndef __SLGMIDI_H__
#define __SLGMIDI_H__

#include "RtMidi.h"
using namespace std;

class slgMidi{

public:
	slgMidi();
	~slgMidi();

public:
	void Setup();
	void Info();
	void set_input_port(unsigned int input);
	void set_output_port(unsigned int output);
	void Start(RtMidiIn::RtMidiCallback callback);
	void set_message(std::vector<unsigned char> message);
	void SendMessage(std::vector<unsigned char> message);
	

private:
	RtMidiIn * m_midiin;
	RtMidiOut * m_midiout;
	std::vector<unsigned char> m_message;


};

#endif