#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "armcm0.h"

typedef struct {
    int head;
    int tail;
    int size;
    uint8_t * data;
} QUEUE;

void queue_init(QUEUE * queue, uint8_t * buf, int size);
void queue_reset(QUEUE * queue);
int  enqueue(QUEUE * queue, uint8_t data);
int  dequeue(QUEUE * queue, uint8_t * data);
int  is_queue_empty(QUEUE * queue);
int is_queue_full(QUEUE * queue);
int  queue_size(QUEUE * queue);

#endif //_QUEUE_H_
