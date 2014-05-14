#ifndef __SLGMIDI_H__
#define __SLGMIDI_H__

#include "RtMidi/RtMidi.h"

class slgMidi{

public:
	slgMidi();
	~slgMidi();

public:
	void setup(void * userData=NULL);
	void start(RtMidiIn::RtMidiCallback callback);
	void info();
	void send(std::vector<unsigned char> message);

private:
	RtMidiIn * m_midiin;
	RtMidiOut * m_midiout;
	std::vector<unsigned char> m_message;


};

#endif