#include "Math.h"


int NextPow2(int a){
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

float Normalize(float value, float min, float max){
	return Clamp( (value - min) / (max - min), 0, 1);
}

float Clamp(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}