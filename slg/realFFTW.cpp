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
	
	if (_in!=NULL)
		fftw_free(_in);
		_in = NULL;

	if (_out!=NULL)
		fftw_free(_out);
		_out = NULL;

	if (_fftCoef!=NULL)
		fftw_free(_fftCoef);
		_fftCoef = NULL;

	if (_mag!=NULL)
		free(_mag);
		_mag = NULL;

	if (_phase!=NULL)
		free(_phase);
		_phase = NULL;

	if (_inverse != NULL)
		free(_inversed);
		_inversed = NULL;
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

//-----------------------------------------------------------------------------
// name: hanning()
// desc: make window
//-----------------------------------------------------------------------------
void hanning( SAMPLE * window, unsigned long length )
{
    unsigned long i;
    double pi, phase = 0, delta;

    pi = 4.*atan(1.0);
    delta = 2 * pi / (double) length;

    for( i = 0; i < length; i++ )
    {
        window[i] = (SAMPLE)(0.5 * (1.0 - cos(phase)));
        phase += delta;
    }
}




//-----------------------------------------------------------------------------
// name: hamming()
// desc: make window
//-----------------------------------------------------------------------------
void hamming( SAMPLE * window, unsigned long length )
{
    unsigned long i;
    double pi, phase = 0, delta;

    pi = 4.*atan(1.0);
    delta = 2 * pi / (double) length;

    for( i = 0; i < length; i++ )
    {
        window[i] = (SAMPLE)(0.54 - .46*cos(phase));
        phase += delta;
    }
}



//-----------------------------------------------------------------------------
// name: blackman()
// desc: make window
//-----------------------------------------------------------------------------
void blackman( SAMPLE * window, unsigned long length )
{
    unsigned long i;
    double pi, phase = 0, delta;

    pi = 4.*atan(1.0);
    delta = 2 * pi / (double) length;

    for( i = 0; i < length; i++ )
    {
        window[i] = (SAMPLE)(0.42 - .5*cos(phase) + .08*cos(2*phase));
        phase += delta;
    }
}




//-----------------------------------------------------------------------------
// name: apply_window()
// desc: apply a window to data
//-----------------------------------------------------------------------------
void applyWindow( SAMPLE * data, SAMPLE * window, unsigned long length )
{
    unsigned long i;

    for( i = 0; i < length; i++ )
        data[i] *= window[i];
}

