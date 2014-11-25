#include "slgOsc.h"
#include "math.h"
#include <stdlib.h> /* same as <cstdlib> included for rand() function */
#include <time.h> /* same as <ctime> to seed rand*/


slgOsc::slgOsc(){
	_sampling_rate = kSampleRate;
	_index = 0;
	_mode = kSin;
	srand (time(NULL));
}

slgOsc::slgOsc(float frequency){
	_sampling_rate = kSampleRate;
	_index = 0;
	_frequency = frequency;
}

slgOsc::~slgOsc(){

}

void slgOsc::set_frequency(float frequency){
	_frequency = frequency;
}

void slgOsc::set_mode(oscillator_mode mode){
	_mode = mode;
}

void slgOsc::set_sampling_rate(unsigned int sampling_rate){
	_sampling_rate = sampling_rate;
}

void slgOsc::set_index(unsigned int index){
	_index = index;
}

SAMPLE slgOsc::render(){
	SAMPLE result;
	switch(_mode){
		case kSin:
			result = sin(2*M_PI*_frequency*_index/(float)_sampling_rate);
			break;
		case kNoise:
			//normalized 
			float r = rand()/(float)RAND_MAX;
			//from -1.0 to 1.0
			result = r*2-1;
			break;
	}
	
	_index++;
	return(result);
}

