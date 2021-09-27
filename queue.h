#ifndef __QUEUE_H__
#define __QUEUE_H__ 

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_MAX_SIZE        (100)

typedef struct queue_tag 
{
    uint8_t rear ;
    uint8_t front ; 
    uint8_t size ; 
    uint8_t entry[QUEUE_MAX_SIZE];
}queue_t ; 

void queue_init(queue_t * queue); 
void queue_deinit(queue_t * queue);
void queue_append(queue_t * queue , uint8_t data);
uint8_t queue_serve(queue_t *queue );
bool queue_is_empty(queue_t * queue );
bool queue_is_full(queue_t *queue);
uint8_t queue_get_size(queue_t *queue);

#endif /*__QUEUE_H__*/
