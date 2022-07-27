#include "edev.h"
static void* ev_global_lock = 0;
static uint8_t ev_absolute_global_lock_en = 0;


uint8_t __ev_obj_fun(const ev_obj_t *obj, uint16_t op, void *arg)
{
    ev_obj_assert(obj)
    ev_type_assert(obj)
    ev_op_assert(obj,op)

    if(obj->type->list[op] || obj->type->list[EVO_E(RELAY)])
    {
        #ifdef EV_CONFIG_OS_LOCK_EN
            if(!ev_absolute_global_lock_en)
            {
                if(obj->attr->lock)
                {
                    ev_os_lock(obj->attr->lock);
                }
                uint8_t ret = 0;
                if(obj->type->list[op])
                {
                    ret = obj->type->list[op](obj, arg);
                }
                else if(obj->type->list[EVO_E(RELAY)])
                {
                    ret = obj->type->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
                }
                if(obj->attr->lock)
                {
                    ev_os_unlock(obj->attr->lock);
                }
                return ret;
            }
            else
            {
                if(!ev_global_lock)
                {
                    ev_global_lock = ev_os_lock_create();
                }
                if(ev_global_lock)
                {
                    ev_os_lock(ev_global_lock);
                }
                if(obj->attr->lock)
                {
                    ev_os_lock(obj->attr->lock);
                }
                uint8_t ret = 0;
                if(obj->type->list[op])
                {
                    ret = obj->type->list[op](obj, arg);
                }
                else if(obj->type->list[EVO_E(RELAY)])
                {
                    ret = obj->type->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
                }
                if(obj->attr->lock)
                {
                    ev_os_unlock(obj->attr->lock);
                }
                if(ev_global_lock)
                {
                    ev_os_unlock(ev_global_lock);
                }
                return ret;
            }
        #else
            uint8_t ret = 0;
            if(obj->type->list[op])
            {
                ret = obj->type->list[op](obj, arg);
            }
            else if(obj->type->list[EVO_E(RELAY)])
            {
                ret = obj->type->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
            }
            return ret;
        #endif
    }
    return 0;
}
void ev_obj_fun_absolute_security_en(uint8_t en)
{
    ev_absolute_global_lock_en  = en;
}
uint8_t ev_obj_fun_obj_security_en(const ev_obj_t *obj,uint8_t en)
{
#ifdef EV_CONFIG_OS_LOCK_EN
    if(en)
    {
        if(!obj->attr->lock)
        {
            obj->attr->lock =  ev_os_lock_create();
            if(!obj->attr->lock)
            {
                return 1;
            }
        }
    }
    else
    {
        if(obj->attr->lock)
        {
            ev_os_lock_free(obj->attr->lock);
            obj->attr->lock = 0;
        }
    }
#endif
    return 0;
}
uint8_t _ev_obj_fun_security(const ev_obj_t *obj, uint16_t op, void *arg)
{
    ev_obj_assert(obj)
    ev_type_assert(obj)
    ev_op_assert(obj,op)

#ifdef EV_CONFIG_OS_LOCK_EN
    if(obj->type->list[op] || obj->type->list[EVO_E(RELAY)])
    {
        if(!ev_global_lock)
        {
            ev_global_lock = ev_os_lock_create();
        }
        if(ev_global_lock)
        {
            ev_os_lock(ev_global_lock);
        }
        uint8_t ret = 0;
        if(obj->type->list[op])
        {
            ret = obj->type->list[op](obj, arg);
        }
        else if(obj->type->list[EVO_E(RELAY)])
        {
            ret = obj->type->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
        }
        if(ev_global_lock)
        {
            ev_os_unlock(ev_global_lock);
        }
        return ret;
    }
    return 0;
#else
    return __ev_obj_fun(obj,op,arg);
#endif
}

