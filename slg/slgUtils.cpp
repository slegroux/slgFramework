#include "slgUtils.h"

float normalize(float value, float min, float max){
	return ((value - min) / (max - min));
}

void updateFPS(float frame){
	float duration_frame = 1.0f / (float)frame_rate;
	float duration_frame_ms = (int)(1000.0f * duration_frame);
    time_difference = glutGet(GLUT_ELAPSED_TIME) - previous_time;
    if (time_difference > duration_frame_ms){
      ; // we do nothing, we are already slower than target frame
    } else {
      int waiting_time = duration_frame_ms - time_difference;
      usleep(waiting_time * 1000); //mac sleep in microseconds - cooler :)
   }
}