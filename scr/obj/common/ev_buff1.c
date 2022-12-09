
#include "./core/ev_core.h"
#include "./obj/common/ev_heap.h"
#include "./obj/common/ev_buff.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_buff1_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,HELP);
    return 0;
}


EV_MODEL_FUN_DEF(ev_buff1_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,INIT);
    if(attr->heap)
    {
        return 1;
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_buff1_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,UNINIT);

    return 0;
}

EV_MODEL_FUN_DEF(ev_buff1_m,MALLOC)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,MALLOC);
    if(attr->heap)
    {
        return 1;
    }

    #ifdef EV_CONFIG_OS_LOCK_EN
        if(!(*attr->buff_lock))
        {
            return 1;
        }
        if(ev_os_lock(*attr->buff_lock))
        {
            return 1;
        }  
    #endif

    uint8_t ret = _ev_do(attr->heap,MALLOC,arg->p,arg->size);

    #ifdef EV_CONFIG_OS_LOCK_EN
        ev_os_unlock(*attr->buff_lock)
    #endif

    return ret;
}


EV_MODEL_FUN_DEF(ev_buff1_m,FREE)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,FREE);
    if(attr->heap)
    {
        return 1;
    }

    #ifdef EV_CONFIG_OS_LOCK_EN
        if(!(*attr->buff_lock))
        {
            return 1;
        }
        if(ev_os_lock(*attr->buff_lock))
        {
            return 1;
        }  
    #endif

    _ev_do(attr->heap,FREE,arg->p);

    #ifdef EV_CONFIG_OS_LOCK_EN
        ev_os_unlock(*attr->buff_lock)
    #endif

    return 0;
}
EV_MODEL_FUN_DEF(ev_buff1_m,BUFF_TAKE)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,BUFF_TAKE);

    if(attr->heap)
    {
        return 1;
    }

    #ifdef EV_CONFIG_OS_LOCK_EN
        if((*attr->buff_lock) == 0)
        {
            (*attr->buff_lock) = ev_os_lock_create(); 
        }
        if(ev_os_lock(*attr->buff_lock))
        {
            return 1;
        }  
    #endif

    if((*attr->master) == 0)
    {
        _ev_do(attr->heap,INIT);
        (*attr->master) = arg->self;
    }

    return 0;
}
EV_MODEL_FUN_DEF(ev_buff1_m,BUFF_GIVE)
{
    EV_MODEL_FUN_GET_ARG(ev_buff1_m,BUFF_GIVE);

    if(attr->heap)
    {
        return 1;
    }
    if((*attr->master) == arg->self)
    {
        _ev_do(attr->heap,UNINIT);
        (*attr->master) = 0;
    }
    #ifdef EV_CONFIG_OS_LOCK_EN
        if(*attr->buff_lock)
        {
            ev_os_unlock(*attr->buff_lock);
        }
    #endif

    return 0;
}

EV_MODEL_LIST_DEF(ev_buff1_m,HELP,INIT,UNINIT,MALLOC,FREE,BUFF_TAKE,BUFF_GIVE);

const ev_model_t ev_buff1_m = EV_MODEL_DEF(ev_buff1_m);
