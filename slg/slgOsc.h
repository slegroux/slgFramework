#ifndef __SLGOSC_H__
#define __SLGOSC_H__

#include "Definitions.h"

enum oscillator_mode{
	kSin,
	kSaw,
	kPulse,
	kNoise,
	kImpulse
};

class slgOsc{

public:
	//TO DO: replace osc by oscillator and render by tick
	slgOsc();
	slgOsc(float frequency);
	~slgOsc();
	void set_mode(oscillator_mode mode);
	void set_frequency(float frequency);
	float get_frequency();
	void set_sampling_rate(unsigned int sampling_rate);
	void set_index(unsigned int index);
	SAMPLE render();

private:
	oscillator_mode _mode;
	float _frequency, _phase;;
	unsigned int _index;
	unsigned int _sampling_rate;
};

#endif