//
// Programmer: Sylvain Le Groux <slegroux@stanford.edu>
// Description: C++ Wrapper for fftw3 library
//

#include <iostream>
#include <sstream>
#include <fftw3.h>
#include <math.h>
#include <cstring>

#ifndef __REALFFTW_H__
#define __REALFFTW_H__

using namespace std;


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
	double *_in, *_mag, *_phase, *_inversed;
	fftw_complex* _out, *_fftCoef;
	fftw_plan _forward,_inverse;
	int _N;	
};

#endif
