#ifndef __SLG_CIRCULAR_BUFFER_H__
#define __SLG_CIRCULAR_BUFFER_H__

#include "Definitions.h"
#include "RtAudio.h"

typedef struct{
	SAMPLE element;
} ElemType;

template <typename TElement>
class slgCircularBuffer{
public:
	slgCircularBuffer(unsigned int size_ring_buffer);
	slgCircularBuffer();
	~slgCircularBuffer();
	TElement Read();
	void Write(TElement element);
	void Empty();
	bool isFull();
	void Print();
	//total size of buffer
	unsigned int get_size();
	//num of elements that have been written so far
	unsigned int get_num_elements();
	unsigned int get_write_idx();
	unsigned int get_read_idx();
	void set_size(unsigned int ring_buffer_size);

private:
	unsigned int _size_ring_buffer;
	TElement *_data;
	//protected: // make it accessible to the derived class
	unsigned int _read_idx;
	unsigned int _write_idx;
	unsigned int _num_elements;

};

//-------------------------------------------
template <typename TElement>
slgCircularBuffer<TElement>::slgCircularBuffer(unsigned int size){
	_size_ring_buffer = size + 1;
	_data = NULL;
	_data = new TElement[_size_ring_buffer];
	memset(_data,0,_size_ring_buffer*sizeof(TElement));
	_read_idx = 0;
	_write_idx = 0;
	_num_elements = 0;
}

template <typename TElement>
slgCircularBuffer<TElement>::slgCircularBuffer(){
	_data = NULL;
	_read_idx = 0;
	_write_idx = 0;
	_num_elements = 0;
}

template <typename TElement>
void slgCircularBuffer<TElement>::set_size(unsigned int size){
	_size_ring_buffer = size + 1;
	_data = new TElement[_size_ring_buffer];
	memset(_data,0,_size_ring_buffer*sizeof(TElement));
}

template <typename TElement>
slgCircularBuffer<TElement>::~slgCircularBuffer(){
	if(_data!= NULL){
		delete [] _data;
		_data = NULL;
		std::cout<<"delete"<<std::endl;
	}
}

// enqueue
template <typename TElement>
void slgCircularBuffer<TElement>::Write(TElement element){
	if ((_write_idx +1)%_size_ring_buffer == _read_idx){
		//std::cout<<"no morecapacity"<<std::endl;
		for (int i =0;i<_size_ring_buffer;i++)
		_data[i] = 0;
	}

	_data[_write_idx] = element;
	_write_idx = (_write_idx + 1) %_size_ring_buffer;
	_num_elements ++;
}

// dequeue
template <typename TElement>
TElement slgCircularBuffer<TElement>::Read(){
	
	if (_read_idx==_write_idx){
		//std::cout<<"nothing to read"<<std::endl;
	}
	
	TElement data_read;
	data_read = _data[_read_idx];
	_read_idx = (_read_idx + 1) % _size_ring_buffer;
	_num_elements --;
	return data_read;
}

template <typename TElement>
void slgCircularBuffer<TElement>::Empty(){
	//memset(_data,0,_size_ring_buffer*sizeof(TElement));
	for (int i =0;i<_size_ring_buffer;i++)
		_data[i] = 0;
	_read_idx = 0;
	_write_idx = 0;
}

template <typename TElement>
void slgCircularBuffer<TElement>::Print(){
	/*for (int i = 0;i<_size_ring_buffer;++i){
		std::cout<<"i: "<<i<<" data: "<<_data[i]<<std::endl;
	}*/
}

template <typename TElement>
bool slgCircularBuffer<TElement>::isFull(){
	if ((_write_idx + 1)%_size_ring_buffer == _read_idx)
		return(TRUE);
	else
		return(FALSE);
}

template <typename TElement>
unsigned int slgCircularBuffer<TElement>::get_write_idx(){
	return(_write_idx);
}

template <typename TElement>
unsigned int slgCircularBuffer<TElement>::get_read_idx(){
	return(_read_idx);
}

template <typename TElement>
unsigned int slgCircularBuffer<TElement>::get_size(){
	return(_size_ring_buffer);
}

template <typename TElement>
unsigned int slgCircularBuffer<TElement>::get_num_elements(){
	return(_num_elements);
}

#endif
