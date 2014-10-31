#ifndef __SLG_CIRCULAR_BUFFER_H__
#define __SLG_CIRCULAR_BUFFER_H__

#include "Definitions.h"
#include "RtAudio.h"

class slgCircularBuffer{
public:
	slgCircularBuffer(unsigned int ring_buffer_size);
	slgCircularBuffer();
	~slgCircularBuffer();
	void Read(SAMPLE *read_buffer, unsigned int size_read_buffer);
	bool Write(SAMPLE *write_buffer, unsigned int size_write_buffer);
	void Empty();
	bool isFull();
	void Print();
	//total size of buffer
	unsigned int get_size();
	//num of elements that have been written so far
	//unsigned int get_num_elements();
	unsigned int get_write_idx();
	unsigned int get_read_idx();
	void get_data(SAMPLE *data,unsigned int size_data);
	void set_size(unsigned int ring_buffer_size);


private:
	unsigned int _size_ring_buffer;
	//unsigned int _num_elements_ring_buffer;
	int _read_idx;
	int _write_idx;
	SAMPLE *_data;
};

#endif
