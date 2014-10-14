#include "realFFTW.h"
#include <time.h>
#include <math.h>       /* sin */
#include <cstring>
#include <iostream> 
#include <fstream>

#define PI 3.14159265

using namespace std;

template <class TBuffer> void makeSine(TBuffer *buffer, float frequency, float duration, int sampleRate);
template <class TBuffer> void buff2txt(TBuffer *buffer, int bufferSize, string filename);
void buff2txt(fftw_complex *buffer, int bufferSize, string filename);
//void buff2txt(float *buffer, int bufferSize, string filename);

int main(int argc, char** argv)
{
	// INPUT
	double *in;
	int buffSize = 8000;
	int fftSize = (buffSize/2)+1;
	in = new double[buffSize];
	//memset(in, 0, buffSize*sizeof(float));
	
	makeSine(in, 2000,1,8000);
	//buff2txt(in,buffSize,"mysine.txt");
	srand(time(NULL)); //seeding*/
	
	/*buffSize = 12;
	double array[] = {0.1, 0.6, 0.1, 0.4, 0.5, 0, 0.8, 0.7, 0.8, 0.6, 0.1,0};
	memcpy(in,array,buffSize*sizeof(double));*/

	realFFTW myfft(buffSize);

	myfft.setInput(in, buffSize);
	myfft.forwardTransform();

	//Magnitude
	double *magnitude;
	magnitude = new double[fftSize];
	myfft.getMagnitude(magnitude,fftSize);
	buff2txt(magnitude,fftSize,"mag.txt");
	myfft.getMagnitudeDB(magnitude,fftSize);
	buff2txt(magnitude,fftSize,"magDB.txt");

	//Phase
	double *phase;
	phase = new double[fftSize];
	myfft.getPhase(phase,fftSize);
	buff2txt(phase,fftSize,"phase.txt");

	// construct fft coeff for inverse processing
	fftw_complex *fft_cpx;
	fft_cpx = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*fftSize);
	for(int j=0;j<fftSize;j++){
		fft_cpx[j][0] = (magnitude[j]*cos(phase[j]));  //Construct new real component
		fft_cpx[j][1] = (magnitude[j]*sin(phase[j]));  //Construct new imaginary  component
	}

	//copy to fftcoef
	myfft.setFFTCoef(fft_cpx,fftSize);	
	//compute inverse
	myfft.inverseTransform();
	//create array to copy the result of computation
	double *inversed;
	inversed = new double[buffSize];
	//copy result of fftw inverse computation to inversed array
	myfft.getInversed(inversed,buffSize);
	//export result to text
	buff2txt(inversed,buffSize,"inversed.txt");
	
	//clean up buffers
	delete [] in;
	delete [] magnitude;
	delete [] phase;
	delete [] inversed;
	delete [] fft_cpx;
	
	return 0;
}

template <class TBuffer>
void makeSine(TBuffer *buffer, float frequency, float duration, int sampleRate){
	
	int N = sampleRate * duration;

	//float buffer[N];
	for (int i=0;i<N;i++){
		buffer[i] = sin(2*PI*frequency*i/(float)sampleRate);
	}
}

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
