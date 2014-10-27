//
// Programmer: Sylvain Le Groux <slegroux@stanford.edu>
// Description: C++ Wrapper for fftw3 library
//

#include <iostream>
#include <sstream>
#include <fftw3.h>
#include <math.h>
#include <cstring>
#include "Definitions.h"

#ifndef __REALFFTW_H__
#define __REALFFTW_H__

using namespace std;

void hanning( SAMPLE * window, unsigned long length );
void hamming( SAMPLE * window, unsigned long length );
void blackman( SAMPLE * window, unsigned long length );
void applyWindow( SAMPLE * data, SAMPLE * window, unsigned long length);

class realFFTW{

public:	
	realFFTW(int N);
	~realFFTW();
	void setInput(double* buffer, int buffSize);
	void getMagnitude(double* buffer, int buffSize);
	void getMagnitudeDB(double* buffer, int buffSize);
	void getPhase(double* buffer, int buffSize);
	void setFFTCoef(fftw_complex* buffer, int buffSize);
	void getInversed(double* buffer, int buffSize);
	void cpyOutput(fftw_complex* buffer, int buffSize);
	//void Spectrum(fftw_complex* buffer, int bufferSize);
	void setIn(int index, double value);
	double getIn(int index);
	void createPlan();
	void destroyPlan();
	int forwardTransform();
	int inverseTransform();
	void getOut(int index);

private:
	double *_in = NULL, *_mag = NULL, *_phase = NULL, *_inversed =NULL;
	fftw_complex* _out = NULL, *_fftCoef = NULL;
	fftw_plan _forward,_inverse;
	int _N;	
};

#endif
