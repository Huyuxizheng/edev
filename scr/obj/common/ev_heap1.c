
#include "./core/ev_core.h"
#include "./obj/common/ev_heap.h"
#include "edev_config.h"

typedef struct {
    uint32_t f:1;
    uint32_t size:32;
}block_h_t;

#define BLOCKH_LEN sizeof(block_h_t)
EV_MODEL_FUN_DEF(ev_heap1_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,HELP);
    return 0;
}


EV_MODEL_FUN_DEF(ev_heap1_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,INIT);

    if((attr->mem_p)&&(attr->mem_size >= 32))
    {
        ((block_h_t *)attr->mem_p)->f = 0;
        ((block_h_t *)attr->mem_p)->size = attr->mem_size - BLOCKH_LEN;

        ev_info("heap1:%x size:%d init  [OK]",attr->mem_p,((block_h_t *)attr->mem_p)->size);
        return 0;
    }

    return 1;
}

EV_MODEL_FUN_DEF(ev_heap1_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,UNINIT);

    if((attr->mem_p)&&(attr->mem_size >= 32))
    {
        ((block_h_t *)attr->mem_p)->f = 0;
        ((block_h_t *)attr->mem_p)->size = 0;
        return 0;
    }

    return 1;
}

static uint8_t *search_free_block(uint8_t *mem_p,uint32_t mem_size,uint8_t* *fast_p,uint32_t size)
{
    uint8_t *end_p = mem_p+mem_size-BLOCKH_LEN;
    uint8_t *free_block = 0;
    block_h_t temp = {0};

    size += BLOCKH_LEN;

    for(uint8_t *block_i = *fast_p;block_i < end_p; block_i += ((block_h_t *)block_i)->size)
    {
        if((((block_h_t *)block_i)->f == 0) && (((block_h_t *)block_i)->size <= size))
        {
            temp = *((block_h_t *)block_i);
            ((block_h_t *)block_i)->f = 1;
            ((block_h_t *)block_i)->size = size;
            free_block = block_i;
            if((block_i + size) < end_p)
            {
                block_i += size;
                ((block_h_t *)block_i)->f = 0;
                ((block_h_t *)block_i)->size = temp.size - size;
                *fast_p = block_i;
            }
            else
            {
                ((block_h_t *)block_i)->size = (uint32_t)(end_p - block_i);
                *fast_p = mem_p;
            }
            return free_block+BLOCKH_LEN;
        }
    }
    return 0;
}

EV_MODEL_FUN_DEF(ev_heap1_m,MALLOC)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,MALLOC);

    if(arg->size)
    if((attr->mem_p)&&(attr->mem_size >= 32))
    {
        if(*(attr->fast_p) == 0)
        {
            *(attr->fast_p) = attr->mem_p;
        }
        *(arg->p) = search_free_block(attr->mem_p,attr->mem_size,attr->fast_p,arg->size);
        if(*(arg->p))
        {
            return 0;
        }
    }

    return 1;
}

static uint8_t delete_block(uint8_t *mem_p,uint32_t mem_size,uint8_t* *fast_p,uint8_t *p)
{
    uint8_t *end_p = mem_p+mem_size-BLOCKH_LEN;
    uint8_t *last_block = 0;
    block_h_t temp = {0};

    p -= BLOCKH_LEN;

    for(uint8_t *block_i = mem_p;block_i < end_p; last_block = block_i,block_i += ((block_h_t *)block_i)->size)
    {
        if(block_i == p)
        {
            uint8_t *next_block = block_i+((block_h_t *)block_i)->size;
            if((last_block) && (((block_h_t *)last_block)->f == 0))
            {
                ((block_h_t *)last_block)->size += ((block_h_t *)block_i)->size;
                block_i = last_block;
            }

            if((next_block < end_p) && (((block_h_t *)next_block)->f == 0))
            {
                ((block_h_t *)block_i)->size += ((block_h_t *)next_block)->size;
            }
            if(block_i < (*fast_p))
            {
                (*fast_p) = block_i;
            }
            return 0;
        }
    }
    return 1;
}
EV_MODEL_FUN_DEF(ev_heap1_m,FREE)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,FREE);

    if((attr->mem_p)&&(attr->mem_size >= 32))
    if(((uint8_t *)arg->p >= (attr->mem_p+BLOCKH_LEN)) && ((uint8_t *)arg->p <= (attr->mem_p + attr->mem_size)))
    {
        return delete_block(attr->mem_p, attr->mem_size,attr->fast_p,arg->p);
    }

    return 1;
}

EV_MODEL_LIST_DEF(ev_heap1_m,HELP,INIT,UNINIT,MALLOC,FREE);

const ev_model_t ev_heap1_m = EV_MODEL_DEF(ev_heap1_m);
