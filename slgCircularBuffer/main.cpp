#include "slgCircularBuffer.h"
#include "slgCircularBuffer2D.h"
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	// play with STL queues

	queue <vector<int> > my_queue;
	vector<int> first(3,0);
	vector<int> second(5,1);
	int thedata[] = {45, 34, 56, 27, 71, 50, 62};
	my_queue.push(first);
	my_queue.push(second);

	vector<int> temp;
	temp = my_queue.front();
	my_queue.pop();
	cout<<"first elem of first vect "<<temp[0]<<endl;
	temp=my_queue.front();
	cout<<"first elem of second vect "<<temp[0]<<endl;

	// play with my ring buffer
	SAMPLE* array;
	array = new SAMPLE[3];
	SAMPLE* array2 = new SAMPLE[3];

	SAMPLE* buf = new SAMPLE[3];
	
	for (int i =0;i<3;++i){
		array[i] = i;
		array2[i] = 2*i;
	}

	// 5 rows of sample*
	slgCircularBuffer<SAMPLE *> ring_buffer(5);

	ring_buffer.Write(array);
	ring_buffer.Write(array2);

	ring_buffer.Write(array);
	ring_buffer.Write(array2);
	buf = ring_buffer.Read();
	for (int i =0;i<3;++i)
		cout<<buf[i]<<endl;
	buf = ring_buffer.Read();
	buf = ring_buffer.Read();

	/*ring_buffer.Write(6.0);
	ring_buffer.Write(7.0);

	ring_buffer.Print();

	cout<<ring_buffer.Read()<<endl;
	ring_buffer.Print();

	cout<<"----------------"<<endl;
	ring_buffer.Empty();
	ring_buffer.Print();*/

	slgCircularBuffer2D<SAMPLE> ring_buffer_2d(3,2);
	//ring_buffer_2d.Write();
	
	return 0;
}

