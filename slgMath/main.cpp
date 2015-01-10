#include "slgMath.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	cout<<"Next pow of 2 after 500: "<<NextPow2(500)<<endl;
	cout<<"Clamp 5 to [-2,2]: "<<Clamp(5,-2,2)<<endl;
	cout<<"Normalize 0 in [-10,10]: "<<Normalize(0, -10, 10)<<endl;
	//random seed 
	srand(time(NULL));
	for (int i =0;i<10;i++)
		cout<<"Random between [-2,5]: "<<Random(-2,2)<<endl;

	return 0;
}

