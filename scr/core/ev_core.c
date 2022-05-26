#include "edev.h"
static void* ev_global_lock = 0;
static uint8_t ev_absolute_global_lock_en = 0;
void ev_obj_free(ev_obj_s *obj)
{
    if(!obj)
    {
        return ;
    }
    if(obj->vals)
    {
        if(obj->type && obj->type->vals_free)
        {
            obj->type->vals_free(obj->vals);
        }
        else
        {
            ev_warning("ev_obj_free no vals_free\r\n"); 
        }
    }
    ev_free(obj);
    return;
}


ev_obj_s* ev_obj_create(ev_type_s *type)
{
    ev_obj_s *obj = ev_malloc(sizeof(ev_obj_s));

    if(!obj)
    {
        ev_warning("ev_obj_create ev_malloc fail\r\n"); 
        return 0;
    }
    if(type)
    {
        obj->type = type;
        if(type->vals_create)
        {
            if(type->vals_create(obj) != 0)
            {
                ev_warning("%s vals_create fail\r\n",type->name); 
                ev_obj_free(obj);
                return 0;
            }
        }

    }
    else
    {
        obj->type = 0;
        obj->vals = 0;
    }
    obj->lock = 0;
    ev_info("%s created success\r\n",type->name);
    return obj;
}

uint8_t _ev_obj_fun(ev_obj_s *obj, uint16_t op, void *arg)
{
    ev_obj_assert(obj)
    ev_type_assert(obj)
    ev_op_assert(obj,op)

    if(obj->type->list[op])
    {
        if(!ev_absolute_global_lock_en)
        {
            if(obj->lock)
            {
                ev_os_lock(obj->lock);
            }
            uint8_t ret = obj->type->list[op](obj, arg);
            if(obj->lock)
            {
                ev_os_unlock(obj->lock);
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
            uint8_t ret = obj->type->list[op](obj, arg);
            if(ev_global_lock)
            {
                ev_os_unlock(ev_global_lock);
            }
            return ret;
        }
    }
    return 0;
}
void ev_obj_fun_absolute_security_en(uint8_t en)
{
    ev_absolute_global_lock_en  = en;
}
uint8_t ev_obj_fun_obj_security_en(ev_obj_s *obj,uint8_t en)
{
    if(en)
    {
        if(!obj->lock)
        {
            obj->lock =  ev_os_lock_create();
            if(!obj->lock)
            {
                return 1;
            }
        }
    }
    else
    {
        if(obj->lock)
        {
            ev_os_lock_free(obj->lock);
            obj->lock = 0;
        }
    }
    return 0;
}
uint8_t _ev_obj_fun_security(ev_obj_s *obj, uint16_t op, void *arg)
{
    ev_obj_assert(obj)
    ev_type_assert(obj)
    ev_op_assert(obj,op)

    if(obj->type->list[op])
    {
        if(!ev_global_lock)
        {
            ev_global_lock = ev_os_lock_create();
        }
        if(ev_global_lock)
        {
            ev_os_lock(ev_global_lock);
        }
        uint8_t ret = obj->type->list[op](obj, arg);
        if(ev_global_lock)
        {
            ev_os_unlock(ev_global_lock);
        }
        return ret;
    }
    return 0;
}




