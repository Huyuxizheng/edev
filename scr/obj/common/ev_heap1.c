
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
        ((block_h *)mem_p)->f = 0;
        ((block_h *)mem_p)->size = attr->mem_size - BLOCKH_LEN;

        ev_info("heap1:%x size:%d init  [OK]",mem_p,((block_h *)mem_p)->size);
        return 0;
    }

    return 1;
}

EV_MODEL_FUN_DEF(ev_heap1_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,UNINIT);

    if((attr->mem_p)&&(attr->mem_size >= 32))
    {
        ((block_h *)mem_p)->f = 0;
        ((block_h *)mem_p)->size = 0;
        return 0;
    }

    return 1;
}

static uint8_t *search_free_block(uint8_t *mem_p,uint32_t mem_size,uint8_t *fast_p,uint32_t size)
{

}

EV_MODEL_FUN_DEF(ev_heap1_m,MALLOC)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,MALLOC);

    if((attr->mem_p)&&(attr->mem_size >= 32))
    {
        if(*(attr->fast_p) != 0)
        {
            search_free_block(uint8_t *mem_p,uint32_t mem_size,uint8_t *fast_p,uint32_t size)
        }
        else
        {


        }
        return 0;
    }

    return 1;
}


EV_MODEL_FUN_DEF(ev_heap1_m,FREE)
{
    EV_MODEL_FUN_GET_ARG(ev_heap1_m,FREE);

    if((attr->mem_p)&&(attr->mem_size >= 32))
    {
        return 0;
    }

    return 1;
}

EV_MODEL_LIST_DEF(ev_heap1_m,HELP,INIT,UNINIT,MALLOC,FREE);

const ev_model_t ev_heap1_m = EV_MODEL_DEF(ev_heap1_m);