#include "slgMath.h"
#include <iostream>
using namespace std;
//using namespace slg;

int main(int argc, char** argv)
{
	cout<<"Next pow of 2 after 500: "<<NextPow2(500)<<endl;
	cout<<"Clamp 5 to [-2,2]: "<<Clamp(5,-2,2)<<endl;
	cout<<"Normalize 0 in [-10,10]: "<<Normalize(0, -10, 10)<<endl;
	cout<<"Map 5 in [0,10] to [0,1]: "<<Map(5, 0, 10, 0,1)<<endl;
	
	// random seed 
	// NULL is a time_t pointer http://www.cplusplus.com/reference/ctime/time/
	srand(time(NULL)); 
	for (int i =0;i<10;i++)
		cout<<"Random between [-2,2]: "<<Random(-2,2)<<endl;

	return 0;
}

