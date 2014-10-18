//
// Programmer: Sylvain Le Groux <slegroux@stanford.edu>
// Description: C++ Wrapper for fftw3 library
//

#ifndef __SLGGEN_H__
#define __SLGGEN_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstring>



using namespace std;

typedef double fftw_complex[2];
template <class TBuffer> void makeSine(TBuffer *buffer, float frequency, float duration, float phase=0, int sampleRate=44100);
template <class TBuffer> void buff2txt(TBuffer *buffer, int bufferSize, string filename);
void buff2txt(fftw_complex *buffer, int bufferSize, string filename);

#endif
