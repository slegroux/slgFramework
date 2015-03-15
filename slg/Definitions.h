#ifndef _SLG_DEFINITIONS_H_
#define _SLG_DEFINITIONS_H_

#define SAMPLE double
//typedef double SAMPLE;

// define is a preprocessor directive replacing any text SAMPLE with double e.g.
#define SAMPLE_RATE 44100
#define NUM_CHANNS 2
#define BUFFER_SIZE 512
#define CIRC_RESOLUTION 60              // 60 pts for a circle

// define is untyped, while const is typed

// Audio
const int kSampleRate = 44100;
const int kNumChannels = 2;
const int kAudioBufferSize = 512;
const int kFrameSize = 512;

// Midi
const int kMidiChannel = 0;

// Graphics
const int kCircleResolution = 60;
const int kWindowWidth = 400;
const int kWindowHeight = 300;
const int kInitWindowPosX = 100;
const int kInitWindowPosY = 100;
const float kFarDistance = 100;
const float kNearDistance = 1;

#endif