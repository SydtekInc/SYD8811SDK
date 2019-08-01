#include "queue.h"

void queue_init(QUEUE * queue, uint8_t *buf, int size)
{
    queue->head = queue->tail = 0;
    queue->size = size;
    queue->data = buf;
}

void queue_reset(QUEUE * queue)
{
    queue->head = queue->tail;
}

int enqueue(QUEUE * queue, uint8_t data)
{
    queue->data[queue->tail++] = data;
    if (queue->tail >= queue->size)
        queue->tail = 0;
    return 1;
}

int dequeue(QUEUE * queue, uint8_t * data)
{
    if (queue->head == queue->tail)
        return 0;
    
    *data = queue->data[queue->head++];
    if (queue->head >= queue->size)
        queue->head = 0;
    
    return 1;
}

int is_queue_empty(QUEUE * queue)
{
    return queue->head == queue->tail;
}

int queue_size(QUEUE * queue)
{
    int extra = 0;
    if (queue->head > queue->tail) {
        extra = queue->size;
    }
    return (queue->tail + extra - queue->head);
}
