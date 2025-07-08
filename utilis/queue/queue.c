/*
 * queue.c
 *
 *  Created on: Jul 8, 2025
 *      Author: Vlata
 */

#include "queue.h"
#include <string.h>
#include "mem.h"


/******************************************************************************
* Definitions
******************************************************************************/

/******************************************************************************
* Variables
******************************************************************************/


/******************************************************************************
* Prototypes
******************************************************************************/
queue_t* queue_create(uint32_t _capacity, uint32_t _item_size);

int32_t queue_destroy(queue_t* _this);

int32_t queue_push(queue_t* _this, void* item);

int32_t queue_pop(queue_t* _this, void* _buffer);

int32_t queue_is_full(queue_t* _this);

int32_t queue_is_empty(queue_t* _this);

int32_t queue_get_size(queue_t* _this);

void* queue_get_front(queue_t* _this);

void* queue_get_back(queue_t* _this);
/******************************************************************************
* Code
******************************************************************************/
queue_t* queue_create(uint32_t _capacity, uint32_t _item_size)
{
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if(!queue)
    {
        return NULL;
    }
    void* ptr = (void*)malloc(_item_size * _capacity);
    if(!ptr)
    {
        free(queue);
        return NULL;
    }
    queue->memory = ptr;
    queue->item_size = _item_size;
    queue->item_count = 0;

    queue->max_capacity = _capacity;
    queue->head = 0;
    queue->tail = 0;

    return queue;
}


int32_t queue_destroy(queue_t* _this)
{
    if(!_this)
    {
        return -1;
    }

    free(_this->memory);
    free(_this);
    return 0;
}

int32_t queue_push(queue_t*  _this, void* _item)
{
    if(!_this || !_item || (_this->item_count >= _this->max_capacity))
    {
        return -1;
    }

    if(_this->tail == _this->max_capacity)
    {
        _this->tail = 0;
    }
    else
    {
        _this->tail = _this->tail + 1;
    }

    memcpy(_this->memory + (_this->item_size * _this->tail), _item, _this->item_size);
    _this->item_count++;

    return 0;
}

int32_t queue_pop(queue_t* _this, void* _buffer)
{
    if((!_this) ||  _this->item_count == 0)
    {
        return -1;
    }

    if(_this->head == _this->max_capacity)
    {
        _this->head = 0;
    }
    else
    {
        _this->head = _this->head - 1;
    }

    memcpy(_buffer, _this->memory + (_this->item_size * _this->head), _this->item_size);
    _this->item_count--;

    return 0;
}

int32_t queue_is_full(queue_t* _this)
{
    if(!_this)
    {
        return -1;
    }

    return (_this->item_count == _this->max_capacity);
}

int32_t queue_is_empty(queue_t* _this)
{
    if(!_this)
    {
        return -1;
    }

    return (_this->item_count == 0);
}

int32_t queue_get_size(queue_t *_this)
{
    if(!_this)
    {
        return -1;
    }

    return (_this->item_count);    
}

void* queue_get_front(queue_t* _this)
{
    if(!_this || _this->item_count == 0)
    {
        return NULL;
    }
    return (_this->memory + (_this->head * _this->item_size));
}

void* queue_get_back(queue_t* _this)
{
    if(!_this || _this->item_count == 0)
    {
        return NULL;
    }
    return (_this->memory + (_this->tail * _this->item_size));
}