#include "slgOscillator.h"
#include <math.h>
#include <stdlib.h> /* same as <cstdlib> included for rand() function */
#include <time.h> /* same as <ctime> to seed rand*/
#include <iostream>


slgOscillator::slgOscillator(){
	_sampling_rate = kSampleRate;
	_index = 0;
	_mode = kSin;
	_phase =0;
}

slgOscillator::slgOscillator(float frequency){
	_sampling_rate = kSampleRate;
	_index = 0;
	_phase = 0;
	_frequency = frequency;
}

slgOscillator::~slgOscillator(){

}

void slgOscillator::set_frequency(float frequency){
	_frequency = frequency;
}
float slgOscillator::get_frequency(){
	return(_frequency);
}

void slgOscillator::set_mode(oscillator_mode mode){
	_mode = mode;
}

void slgOscillator::set_sampling_rate(unsigned int sampling_rate){
	_sampling_rate = sampling_rate;
}

void slgOscillator::set_index(unsigned int index){
	_index = index;
}

SAMPLE slgOscillator::render(){
	SAMPLE result;
	switch(_mode){
		case kSin:
			result = sin(_phase);
			_phase += 2*M_PI*_frequency/(float)_sampling_rate;
			//result = sin(2*M_PI*_frequency*_index/(float)_sampling_rate);
			/*if (_phase > (2 * M_PI)){
				_phase = _phase - (2 * M_PI);
				std::cout<<"toto"<<std::endl;
			}*/

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

