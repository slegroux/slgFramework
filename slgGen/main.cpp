#include "slgGen.h"
//#include "slg2D.h"
using namespace std;

int main(int argc, char** argv)
{
	// INPUT
	double *in;
	int buffSize = 8000;
	int fftSize = (buffSize/2)+1;
	in = new double[buffSize];
	//memset(in, 0, buffSize*sizeof(float));
	
	makeSine(in, 2000,1,8000);
	buff2txt(in,buffSize,"Sine.txt");
	
	
	/*buffSize = 12;
	double array[] = {0.1, 0.6, 0.1, 0.4, 0.5, 0, 0.8, 0.7, 0.8, 0.6, 0.1,0};
	memcpy(in,array,buffSize*sizeof(double));*/

	/*realFFTW myfft(buffSize);

	myfft.setInput(in, buffSize);
	myfft.forwardTransform();

	//Magnitude
	double *magnitude;
	magnitude = new double[fftSize];
	myfft.getMagnitude(magnitude,fftSize);
	buff2txt(magnitude,fftSize,"mag.txt");

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
	delete [] fft_cpx;*/
	
	return 0;
}

