#include "realFFTW.h"

realFFTW::realFFTW(int N){
	_N = N;
	_in = (double *) fftw_malloc(sizeof(double) * _N);
	_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (_N/2+1));
	_fftCoef = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (_N/2+1));
	_mag = (double *) malloc(_N*sizeof(double));
    _phase = (double *) malloc(_N*sizeof(double));
    _inversed = (double *) malloc(_N*sizeof(double));
	//fftw plan for fft 1 dimensional, real signal
	_forward = fftw_plan_dft_r2c_1d(_N, _in, _out, FFTW_ESTIMATE);
	//Setup fftw plan for ifft 1 dimensional, complex signal
	_inverse = fftw_plan_dft_c2r_1d(_N, _fftCoef, _inversed, FFTW_ESTIMATE);
}

realFFTW::~realFFTW(){
	fftw_destroy_plan(_forward);
	fftw_destroy_plan(_inverse);
	fftw_free(_in);
	fftw_free(_out);
	free(_mag);
	free(_phase);
}

void realFFTW::setInput(double* buffer, int buffSize){
	memcpy(_in,buffer,buffSize*sizeof(double));
}

void realFFTW::setFFTCoef(fftw_complex* buffer, int buffSize){
	memcpy(_fftCoef,buffer,buffSize*sizeof(fftw_complex));
}

void realFFTW::cpyOutput(fftw_complex* buffer, int buffSize){
	memcpy(buffer,_out,buffSize*sizeof(fftw_complex));
}

void realFFTW::setIn(int index, double value){
	*(_in + index) = value;
}

double realFFTW::getIn(int index){
	return(*(_in+index));
}

void realFFTW::getOut(int index){
	//return(*(out + index));
}

void realFFTW::getMagnitude(double* buffer, int buffSize){
	for(int i=0;i<(_N/2)+1;i++){
		//normalization
		_mag[i] = (2./_N)*sqrt((_out[i][0]*_out[i][0])+(_out[i][1]*_out[i][1]));
	}
	memcpy(buffer,_mag,buffSize*sizeof(double));
}

void realFFTW::getMagnitudeDB(double* buffer, int buffSize){
	for(int i=0;i<(_N/2)+1;i++){
		//normalization
		_mag[i] = 20*log10((2./_N)*sqrt((_out[i][0]*_out[i][0])+(_out[i][1]*_out[i][1])));
	}
	memcpy(buffer,_mag,buffSize*sizeof(double));
}

void realFFTW::getPhase(double* buffer, int buffSize){
	for(int i=0;i<(_N/2)+1;i++){
		_phase[i] = atan2(_out[i][0],_out[i][1]);
	}
	memcpy(buffer,_phase,buffSize*sizeof(double));
}

void realFFTW::getInversed(double* buffer, int buffSize){
	memcpy(buffer,_inversed,buffSize*sizeof(double));
}


void realFFTW::createPlan(){
	//fftw plan for fft 1 dimensional, real signal
	_forward = fftw_plan_dft_r2c_1d(_N, _in, _out, FFTW_ESTIMATE);
	//Setup fftw plan for ifft 1 dimensional, complex signal
	_inverse = fftw_plan_dft_c2r_1d(_N, _out, _in, FFTW_ESTIMATE);
}

void realFFTW::destroyPlan(){
	fftw_destroy_plan(_forward);
	fftw_destroy_plan(_inverse);	
}

int realFFTW::forwardTransform(){
	if (_forward!=NULL){
		fftw_execute(_forward);
		return 1;
	}
	else{
		cout<<"Error: forward plan not initialized"<<endl;
		return 0;
	}
}

int realFFTW::inverseTransform(){
	if (_inverse!=NULL){
		fftw_execute(_inverse);
		return 1;
	}
	else{
		cout<<"Error: inverse plan not initialized"<<endl;
		return 0;
	}
}
