#include "queue.h"

void queue_init(queue_t * queue)
{
    queue->rear = 0; 
    queue->front = 0; 
    queue->size  =0;
}

void queue_deinit(queue_t * queue)
{
    queue->rear = 0; 
    queue->front = 0; 
    queue->size  =0;
}

void queue_append(queue_t * queue , uint8_t data)
{
    queue->entry[queue->rear] =  data; 
    queue->rear = (queue->rear + 1) % QUEUE_MAX_SIZE ;
    queue->size ++; 
}

uint8_t queue_serve(queue_t *queue)
{
    uint8_t ret ; 
    ret = queue->entry[queue->front] ; 
    queue->front =(queue -> front + 1) % QUEUE_MAX_SIZE ;
    queue->size -- ; 
    return ret ; 
}

bool queue_is_empty(queue_t * queue )
{
    return !(queue->size) ; 
}

bool queue_is_full(queue_t *queue)
{
    return (queue->size >= QUEUE_MAX_SIZE);
}

uint8_t queue_get_size(queue_t *queue)
{
    uint8_t ret ; 
    ret = queue->size; 
    return ret ; 
}
