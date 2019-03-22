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

#include <string.h>
#include "queue.h"

void init_queue(QUEUE *queue, void *data_array, size_t item_size, size_t max_num)
{
	if (queue != 0) {
		queue->num = 0;
		queue->start = 0;
		queue->data = data_array;
		queue->item_size = item_size;
		queue->max_num = max_num;
	}
}

void clear_queue(QUEUE *queue)
{
	if (queue != 0) {
		queue->num = 0;
		queue->start = 0;
	}
}

int enqueue_queue(QUEUE *queue, const void *data)
{
	if ((queue != 0) && (data != 0) && (queue->num < queue->max_num)) {
		size_t dest_index = (queue->start + queue->num) % queue->max_num;
		void *dest = (char *)queue->data + (queue->item_size * dest_index);
		memcpy(dest, data, queue->item_size);
		queue->num++;
		return 1;
	}
	else {
		return 0;
	}
}

int dequeue_queue(QUEUE *queue, void *data)
{
	if ((queue != 0) && (queue->num > 0)) {
		void *src = (char *)queue->data + (queue->item_size * queue->start);
		if (data != 0) memcpy(data, src, queue->item_size);
		queue->start = (queue->start + 1) % queue->max_num;
		queue->num--;
		return 1;
	}
	else {
		return 0;
	}
}

int at_queue(const QUEUE *queue, size_t index, void *data)
{
	if ((queue != 0) && (queue->num > 0) && (index < queue->num)) {
		if (data != 0) {
			size_t src_index = (queue->start + index) % queue->max_num;
			void *src = (char *)queue->data + (queue->item_size * src_index);
			memcpy(data, src, queue->item_size);
		}
		return 1;
	}
	else {
		return 0;
	}
}

