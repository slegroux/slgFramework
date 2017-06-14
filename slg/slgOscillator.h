#ifndef __SLGOSCILLATOR_H__
#define __SLGOSCILLATOR_H__

#include "Definitions.h"

enum oscillator_mode{
	// TO DO: implement saw, pulse
	kSin,
	kSaw,
	kPulse,
	kNoise,
	kImpulse
};

class slgOscillator{

public:
	//TO DO: replace osc by oscillator and render by tick
	slgOscillator();
	slgOscillator(float frequency);
	~slgOscillator();
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