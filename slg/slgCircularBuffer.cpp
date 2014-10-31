#include "slgCircularBuffer.h"


slgCircularBuffer::slgCircularBuffer(unsigned int size){
	_size_ring_buffer = size;
	_data = NULL;
	_data = new SAMPLE[_size_ring_buffer];
	memset(_data,0,_size_ring_buffer*sizeof(SAMPLE));
	_read_idx = 0;
	_write_idx = 0;
	//_num_elements_ring_buffer = 0;
}

slgCircularBuffer::slgCircularBuffer(){
	_data = NULL;
	_read_idx = 0;
	_write_idx = 0;
	//_num_elements_ring_buffer = 0;
}

void slgCircularBuffer::set_size(unsigned int size){
	_size_ring_buffer = size;
	_data = new SAMPLE[_size_ring_buffer];
	memset(_data,0,_size_ring_buffer*sizeof(SAMPLE));
}

slgCircularBuffer::~slgCircularBuffer(){
	delete [] _data;
	_data = NULL;
}

void slgCircularBuffer::Print(){
	for (int i = 0;i<_size_ring_buffer;i++)
		std::cout<< "i: "<<i<<" "<<_data[i]<<std::endl;
}

void slgCircularBuffer::get_data(SAMPLE *data,unsigned int size_data){
	if (size_data>_size_ring_buffer)
		std::cout<<"over max size of ring buffer"<<std::endl;
	else{
		for (int i=0;i<size_data;i++)
			data[i] = _data[i];
	}
}

void slgCircularBuffer::Read(SAMPLE *read_buffer, unsigned int size_read_buffer){

	for (int i = 0;i<size_read_buffer;i++)
		read_buffer[i] = _data[_read_idx+i];

	_read_idx = (_read_idx + size_read_buffer)%_size_ring_buffer;
	//_num_elements_ring_buffer = (_num_elements_ring_buffer - size_read_buffer)%_size_ring_buffer;		
}

bool slgCircularBuffer::Write(SAMPLE *write_buffer, unsigned int size_write_buffer){
	std::cout<<"write_idx: "<<_write_idx + size_write_buffer<<std::endl;
	if (_write_idx + size_write_buffer>_size_ring_buffer)
		std::cout<<"overwriting data"<<std::endl;

	//We write over old data
	for (int i=0;i<size_write_buffer;i++){
		_data[(_write_idx + i)%_size_ring_buffer] = write_buffer[i];
	}
	_write_idx = (_write_idx +size_write_buffer) %_size_ring_buffer;
	//_num_elements_ring_buffer = (_num_elements_ring_buffer + size_write_buffer)%_size_ring_buffer;
}

void slgCircularBuffer::Empty(){
	memset(_data,0,_size_ring_buffer*sizeof(SAMPLE));
	_read_idx = 0;
	_write_idx = 0;
}

bool slgCircularBuffer::isFull(){
	if (_write_idx >= (_size_ring_buffer-1)%_size_ring_buffer)
		return(TRUE);
	else
		return(FALSE);
}

/*unsigned int slgCircularBuffer::get_num_elements(){
	return(_num_elements_ring_buffer);
}*/
unsigned int slgCircularBuffer::get_write_idx(){
	return(_write_idx);
}
unsigned int slgCircularBuffer::get_read_idx(){
	return(_read_idx);
}
unsigned int slgCircularBuffer::get_size(){
	return(_size_ring_buffer);
}
