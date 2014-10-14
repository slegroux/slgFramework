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

#include "RtMidi/RtMidi.h"
using namespace std;

class slgMidi{

public:
	slgMidi();
	~slgMidi();

public:
	void setup(void * userData=NULL);
	void start(RtMidiIn::RtMidiCallback callback);
	void info();
	void sendMessage(std::vector<unsigned char> message);

private:
	RtMidiIn * m_midiin;
	RtMidiOut * m_midiout;
	std::vector<unsigned char> m_message;


};

#endif