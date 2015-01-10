#include "Math.h"
#include <time.h>//time
#include <stdlib.h>//srand


int NextPow2(int a){
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

float Clamp(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}

float Normalize(float value, float min, float max){
    return Clamp( (value - min) / (max - min), 0, 1);
}

float Random(float min, float max){
	//rand generates random number b/w 0 and RAND_MAX
	float r = (max-min)*rand()/(RAND_MAX+1.0) + min;
	return(r);
}

float Map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
   return ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
}
