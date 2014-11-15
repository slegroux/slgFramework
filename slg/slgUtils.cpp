#include "slgUtils.h"

float normalize(float value, float min, float max){
	return ((value - min) / (max - min));
}

