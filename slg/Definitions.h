#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

// think about typedef maybe?
#define SAMPLE double
//replace by const
#define SAMPLE_RATE 44100
#define NUM_CHANNS 2
#define BUFFER_SIZE 512
#define CIRC_RESOLUTION 60              // 60 pts for a circle

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

#endif