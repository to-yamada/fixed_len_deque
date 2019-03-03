/* 
Copyright 2019 to-yamada

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef	FIXED_LEN_QUEUE_H_INCLUDED
#define	FIXED_LEN_QUEUE_H_INCLUDED

#define DEFINE_FIXED_LEN_QUEUE(T, size, name)								\
struct struct_##name {														\
	unsigned int num;														\
	unsigned int start;														\
	T data[size];															\
};																			\
																			\
static void clear_##name(struct struct_##name *queue)						\
{																			\
	if (queue != 0) {														\
		queue->num = 0;														\
		queue->start = 0;													\
	}																		\
}																			\
																			\
static int enqueue_##name(struct struct_##name *queue, const T *data)		\
{																			\
	if ((queue != 0) && (data != 0) && (queue->num < (size))) {				\
		queue->data[(queue->start + queue->num) % (size)] = *data;			\
		queue->num++;														\
		return 1;															\
	}																		\
	else {																	\
		return 0;															\
	}																		\
}																			\
																			\
static int dequeue_##name(struct struct_##name *queue, T *data)				\
{																			\
	if ((queue != 0) && (queue->num > 0)) {									\
		if (data != 0) *data = queue->data[queue->start];					\
		queue->start = (queue->start + 1) % (size);							\
		queue->num--;														\
		return 1;															\
	}																		\
	else {																	\
		return 0;															\
	}																		\
}																			\
																			\
typedef struct struct_##name name

#endif	/* FIXED_LEN_QUEUE_H_INCLUDED */

