#include "slgGen.h"

template <class TBuffer>
void makeSine(TBuffer *buffer, float frequency, float duration, float phase, int sampleRate){
	
	int NSample = sampleRate * duration;

	//float buffer[N];
	for (int i=0;i<NSample;i++){
		buffer[i] = sin(2*M_PI*frequency*i/(float)sampleRate+phase);
	}
}

template void makeSine(float *buffer, float frequency, float duration, float phase, int sampleRate);
template void makeSine(double *buffer, float frequency, float duration, float phase, int sampleRate);

template <class TBuffer>
void buff2txt(TBuffer *buffer, int bufferSize, string filename){
	ofstream fout;
	fout.open(filename);
	if(fout.is_open()){
		for (int i=0;i<bufferSize;i++){
			fout<<*(buffer+i)<<endl;
			//fout<<buffer[i]<<endl;
		}
	}
	else{
		cout<<"could not open file"<<endl;
	}

	fout.close();
}
template void buff2txt(float *buffer, int bufferSize, string filename);
template void buff2txt(double *buffer, int bufferSize, string filename);


void buff2txt(fftw_complex *buffer, int bufferSize, string filename){
	ofstream fout;
	fout.open(filename);
	if(fout.is_open()){
		for (int i=0;i<bufferSize;i++){
			//fout<<*(buffer+i)<<endl;
			fout<<buffer[i][0] << "\t" << buffer[i][1]<<endl;
		}
	}
	else{
		cout<<"could not open file"<<endl;
	}
	fout.close();
}

