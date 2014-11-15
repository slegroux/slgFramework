#ifndef __SLG_CIRCULAR_BUFFER_2D_H__
#define __SLG_CIRCULAR_BUFFER_2D_H__

#include "Definitions.h"
#include "RtAudio.h"

template <typename TElement>
class slgCircularBuffer2D{
public:
	slgCircularBuffer2D(unsigned int size_ring_buffer, unsigned int size_element);
	slgCircularBuffer2D();
	~slgCircularBuffer2D();
	TElement* Read();
	void Write(TElement *element, unsigned int size_element);
	void Empty();
	bool isFull();
	void Print();
	//total size of buffer
	unsigned int get_size();
	//num of elements that have been written so far
	//unsigned int get_num_elements();
	unsigned int get_write_idx();
	unsigned int get_read_idx();
	void set_size(unsigned int ring_buffer_size, unsigned int size_element);

private:
	unsigned int _size_ring_buffer;
	unsigned int _size_element;
	TElement **_data;
	//protected: // make it accessible to the derived class
	unsigned int _read_idx;
	unsigned int _write_idx;
	unsigned int _num_elements;

};

//-------------------------------------------
template <typename TElement>
slgCircularBuffer2D<TElement>::slgCircularBuffer2D(unsigned int size_buffer, unsigned int size_element){
	_size_ring_buffer = size_buffer + 1;
	_size_element = size_element;
	_data = NULL;
	/*
	int** ary = new int*[sizeX];
	for(int i = 0; i < sizeX; ++i)
	    ary[i] = new int[sizeY];
	*/
	//height
	_data = new TElement*[_size_ring_buffer];
	for (int i=0;i<_size_ring_buffer;i++){
		//width
		_data[i] = new TElement[_size_element];
		memset(_data[i],0,_size_element*sizeof(TElement));
	}
	_read_idx = 0;
	_write_idx = 0;
	_num_elements = 0;
}

template <typename TElement>
slgCircularBuffer2D<TElement>::slgCircularBuffer2D(){
	_data = NULL;
	_read_idx = 0;
	_write_idx = 0;
	_num_elements = 0;
}

template <typename TElement>
void slgCircularBuffer2D<TElement>::set_size(unsigned int buffer_size, unsigned int size_element){
	_size_ring_buffer = buffer_size + 1;
	_size_element = size_element;
	//_data = new TElement[_size_ring_buffer];
	//memset(_data,0,_size_ring_buffer*sizeof(TElement));
}

template <typename TElement>
slgCircularBuffer2D<TElement>::~slgCircularBuffer2D(){
	if(_data!= NULL){
		for (int i= 0;i<_size_ring_buffer;i++){
			delete [] _data[i];
		}
		delete [] _data;
		_data = NULL;
		std::cout<<"delete"<<std::endl;
	}
}

// enqueue
template <typename TElement>
void slgCircularBuffer2D<TElement>::Write(TElement *element, unsigned int element_size){
	// check element_size <= _element_size
	if ((_write_idx +1)%_size_ring_buffer == _read_idx){
		std::cout<<"no morecapacity"<<std::endl;
		for (int i =0;i<_size_ring_buffer;i++){
			for (int j=0;j<_size_element;j++){
				_data[i][j] = 0;
			}
		}
	}

	_data[_write_idx] = element;
	_write_idx = (_write_idx + 1) %_size_ring_buffer;
	_num_elements ++;
}

// dequeue
template <typename TElement>
TElement* slgCircularBuffer2D<TElement>::Read(){
	
	if (_read_idx==_write_idx){
		//std::cout<<"nothing to read"<<std::endl;
	}
	
	TElement *data_read;
	data_read = _data[_read_idx];
	_read_idx = (_read_idx + 1) % _size_ring_buffer;
	_num_elements --;
	return data_read;
}

template <typename TElement>
void slgCircularBuffer2D<TElement>::Empty(){
	//memset(_data,0,_size_ring_buffer*sizeof(TElement));
	for (int i =0;i<_size_ring_buffer;i++)
		_data[i] = 0;
	_read_idx = 0;
	_write_idx = 0;
}

template <typename TElement>
void slgCircularBuffer2D<TElement>::Print(){
	for (int i = 0;i<_size_ring_buffer;++i){
		std::cout<<"i: "<<i<<" data: "<<_data[i]<<std::endl;
	}
}

template <typename TElement>
bool slgCircularBuffer2D<TElement>::isFull(){
	if ((_write_idx + 1)%_size_ring_buffer == _read_idx)
		return(TRUE);
	else
		return(FALSE);
}

template <typename TElement>
unsigned int slgCircularBuffer2D<TElement>::get_write_idx(){
	return(_write_idx);
}

template <typename TElement>
unsigned int slgCircularBuffer2D<TElement>::get_read_idx(){
	return(_read_idx);
}

template <typename TElement>
unsigned int slgCircularBuffer2D<TElement>::get_size(){
	return(_size_ring_buffer);
}


#endif
