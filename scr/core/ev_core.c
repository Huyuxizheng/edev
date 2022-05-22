#include "edev.h"

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
        return obj->type->list[op](obj, arg);
    }
    return 0;
}






