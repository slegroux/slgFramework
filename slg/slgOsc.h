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
	slgOsc();
	slgOsc(float frequency);
	~slgOsc();
	void set_mode(oscillator_mode mode);
	void set_frequency(float frequency);
	void set_sampling_rate(unsigned int sampling_rate);
	void set_index(unsigned int index);
	SAMPLE render();

private:
	oscillator_mode _mode;
	float _frequency;
	unsigned int _index;
	unsigned int _sampling_rate;
};