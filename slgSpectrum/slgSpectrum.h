#ifndef __SLGSPECTRUM_H__
#define __SLGSPECTRUM_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "Definitions.h"
#include "FFT/chuck_fft.h"
#include "FFT/realFFT.h"
#include <math.h>
using namespace std;

class slgSpectrum{

public:
	slgSpectrum();
	~slgSpectrum();
public:
	void init(int bufferSize);
	double* getSpectrum(float *buffer, int bufferSize, string mode="carl");
protected:
	// input
	float *_buffer;
	int _bufferSize;
	// Analysis window
	float *_fftWindow;
	// FFT bins
	double *_fftBuff;
	realFFTData *_fftData;
	realFFT *_rfft;

};

#endif