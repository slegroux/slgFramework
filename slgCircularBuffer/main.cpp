#include "slgCircularBuffer.h"

using namespace std;

int main(int argc, char** argv)
{
	// max size buffer = 8
	slgCircularBuffer ring_buffer(8);
	//ring_buffer= new slgCircularBuffer[8];
	// input buffer size = 10
	std::cout<<"read_idx before: "<<ring_buffer.get_read_idx()<<std::endl;
	SAMPLE out[4];
	SAMPLE in10[10] = {1,2,3,4,5,6,7,8,9,10};
	for (int i=0;i<10;i++){
		ring_buffer.Write(in10,1);
		std::cout<<"write"<<std::endl;
		std::cout<<"num elements:"<<ring_buffer.get_num_elements()<<std::endl;
		ring_buffer.Read(out,2);
		std::cout<<"read"<<std::endl;
		std::cout<<"num elements:"<<ring_buffer.get_num_elements()<<std::endl;
		std::cout<<"read idx:"<<ring_buffer.get_read_idx()<<std::endl;
		std::cout<<"write idx:"<<ring_buffer.get_write_idx()<<std::endl;
		ring_buffer.Print();
		for (int i=0;i<3;i++)
			std::cout<<out[i]<<std::endl;
	}


	/*ring_buffer.Write(in10, 6);
	ring_buffer.Print();
	std::cout<<"n_elements: "<<ring_buffer.get_num_elements()<<std::endl;
	std::cout<<"write idx: "<<ring_buffer.get_write_idx()<<std::endl;
	std::cout<<"read idx: "<<ring_buffer.get_read_idx()<<std::endl;
	SAMPLE out[4];
	ring_buffer.Read(out,4);
	for (int i=0;i<4;i++){
		std::cout<<out[i]<<endl;
	}
	std::cout<<"write idx: "<<ring_buffer.get_write_idx()<<std::endl;
	std::cout<<"read idx: "<<ring_buffer.get_read_idx()<<std::endl;
	
	ring_buffer.Read(out,4);
	for (int i=0;i<4;i++){
		std::cout<<out[i]<<endl;
	}

	std::cout<<"write idx: "<<ring_buffer.get_write_idx()<<std::endl;
	std::cout<<"read idx: "<<ring_buffer.get_read_idx()<<std::endl;*/
	

	return 0;
}

