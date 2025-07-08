/*
 * queue.c
 *
 *  Created on: Jul 8, 2025
 *      Author: Vlata
 */

#ifndef QUEUE_C_
#define QUEUE_C_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#ifdef __cpluscplus
extern "C" {
#endif

/******************************************************************************
* Definitions
******************************************************************************/


typedef struct queue_t
{
    void* memory;
    uint32_t item_size;
    uint32_t item_count;
    uint32_t max_capacity;
    uint32_t head;
    uint32_t tail;

} queue_t;


/******************************************************************************
* Prototypes
******************************************************************************/

queue_t* queue_create(int32_t _capacity, int32_t _item_size);

int32_t queue_destroy(queue_t* _this);

int32_t queue_push(queue_t* _this, void* item);

int32_t queue_pop(queue_t* _this, void* _buffer);

int32_t queue_is_full(queue_t* _this);

int32_t queue_is_empty(queue_t* _this);

int32_t queue_get_size(queue_t *_queue);

void* queue_get_front(queue_t* _this);

void* queue_get_back(queue_t* _this);


#ifdef __cpluscplus
};
#endif

#endif /* QUEUE_C_ */
