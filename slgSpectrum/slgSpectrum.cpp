#include "slgSpectrum.h"

slgSpectrum::slgSpectrum(){
    cout<<"Spectrum constructor"<<endl;
    _buffer = NULL;
    _bufferSize = 512;
    _fftWindow = NULL;
    _fftBuff = NULL;
    cout<<"buffer size: "<<_bufferSize<<endl;
}

slgSpectrum::~slgSpectrum(){
    cout<<"Spectrum destructor"<<endl;
    delete [] _buffer;
    _buffer = NULL;
    delete [] _fftWindow;
    _fftWindow = NULL;
    delete [] _fftBuff;
    _fftBuff = NULL;
}

void slgSpectrum::init(int bufferSize){
    cout<<"Spectrum init"<<endl;
    _bufferSize = bufferSize;
    _buffer = new float[_bufferSize];
    memset(_buffer, 0, bufferSize*sizeof(float));
    _fftWindow = new float[_bufferSize];
    memset(_fftWindow, 0, _bufferSize*sizeof(float));
    _fftBuff = new double[_bufferSize/2];
    memset(_fftBuff,0,(_bufferSize/2)*sizeof(float));
    // default to hanning window of size bufferSize
    hanning(_fftWindow, _bufferSize);
    _fftData = new realFFTData(bufferSize);
    _rfft = new realFFT(_fftData);
}

double* slgSpectrum::getSpectrum(float *buffer, int bufferSize, string mode){

    // copy input buffer for processing
    memcpy(_buffer, buffer, _bufferSize*sizeof(float));

    if (!mode.compare("carl")){
    // apply hanning window to input buffer
        apply_window(_buffer,_fftWindow,_bufferSize);
    // zero pad if necessary
    // rfft( g_fftBuff, ZPF * buff erSize / 2, FFT_FORWARD );
    // Apply real FFT analysis on input buffer
        rfft( _buffer, _bufferSize / 2, FFT_FORWARD );
        complex *fft = (complex *) _buffer;
        for (int i = 0;i<_bufferSize/2; ++i)
            _fftBuff[i] = (double)1.8*pow( 25 * cmp_abs( fft[i] ), .5 );
        //_fftBuff[i] = cmp_abs(fft[i]);
        cout<<"carl fftBuff[0]: "<<_fftBuff[0]<<endl;
        return(_fftBuff);
    }
    else if (!mode.compare("fftw")){
        for (int i=0;i<bufferSize;++i){
            _fftData->in[i] = _buffer[i];
        }
        _rfft->fwdTransform();
        cout<<"fftw fftBuff[0]: "<<_fftData->in[0]<<endl;
        return(_fftData->in);
    }
}
