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

typedef struct {
	unsigned int num;
	unsigned int start;
	void *data;
	size_t item_size;
	size_t max_num;
} QUEUE;

#define INIT_QUEUE_ARRAY(queue, array) \
	init_queue((queue), (array), sizeof((array)[0]), sizeof(array) / sizeof((array)[0]))
void init_queue(QUEUE *queue, void *data_array, size_t item_size, size_t max_num);
void clear_queue(QUEUE *queue);
int enqueue_queue(QUEUE *queue, const void *data);
int dequeue_queue(QUEUE *queue, void *data);
int at_queue(const QUEUE *queue, size_t index, void *data);

#endif	/* FIXED_LEN_QUEUE_H_INCLUDED */

