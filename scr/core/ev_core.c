#include "edev.h"

#ifdef EV_CONFIG_OS_LOCK_EN
static void* ev_global_lock = 0;
#endif
static uint8_t ev_absolute_global_lock_en = 0;

static uint8_t ev_call_model_fun(const ev_obj_t *obj,const ev_model_t *model, uint16_t op, void *arg)
{
    if(!model)
    {
        return 0;
    }
    if(op > model->total)
    {
        return ev_call_model_fun( obj, model->parent, op, arg);
    }
    else if(model->list[op])
    {
        return model->list[op](obj, arg);
    }
    else if(model->list[EVO_E(RELAY)])
    {
        return model->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
    }
    else if(model->parent)
    {
        return ev_call_model_fun( obj, model->parent, op, arg);
    }
    return 0;
}
uint8_t __ev_parent_fun(const ev_obj_t *obj, uint16_t op, void *arg)
{
    return ev_call_model_fun( obj, obj->model->parent, op, arg);
}
uint8_t __ev_obj_fun(const ev_obj_t *obj, uint16_t op, void *arg)
{
    ev_obj_assert(obj)
    ev_model_assert(obj)
    ev_op_assert(obj,op)

    if(obj->model->list[op] || obj->model->list[EVO_E(RELAY)] || obj->model->parent)
    {
        #ifdef EV_CONFIG_OS_LOCK_EN
            if(!ev_absolute_global_lock_en)
            {
                if(obj->attr->lock)
                {
                    ev_os_lock(obj->attr->lock);
                }
                uint8_t ret = 0;
                if(op > obj->model->total)
                {
                    ret = ev_call_model_fun(obj, obj->model->parent, op, arg);
                }
                else if(obj->model->list[op])
                {
                    ret = obj->model->list[op](obj, arg);
                }
                else if(obj->model->list[EVO_E(RELAY)])
                {
                    ret = obj->model->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
                }
                else if(obj->model->parent)
                {
                    ret = ev_call_model_fun( obj, obj->model->parent, op, arg);
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
                if(op > obj->model->total)
                {
                    ret = ev_call_model_fun(obj, obj->model->parent, op, arg);
                }
                else if(obj->model->list[op])
                {
                    ret = obj->model->list[op](obj, arg);
                }
                else if(obj->model->list[EVO_E(RELAY)])
                {
                    ret = obj->model->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
                }
                else if(obj->model->parent)
                {
                    ret = ev_call_model_fun(obj, obj->model->parent, op, arg);
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
            if(op > obj->model->total)
            {
                ret = ev_call_model_fun(obj, obj->model->parent, op, arg);
            }
            else if(obj->model->list[op])
            {
                ret = obj->model->list[op](obj, arg);
            }
            else if(obj->model->list[EVO_E(RELAY)])
            {
                ret = obj->model->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
            }
            else if(obj->model->parent)
            {
                ret = ev_call_model_fun(obj, obj->model->parent, op, arg);
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
#ifdef EV_CONFIG_OS_LOCK_EN

    ev_obj_assert(obj)
    ev_model_assert(obj)
    ev_op_assert(obj,op)

    if(obj->model->list[op] || obj->model->list[EVO_E(RELAY)] || obj->model->parent)
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
        if(op > obj->model->total)
        {
            ret = ev_call_model_fun(obj, obj->model->parent, op, arg);
        }
        else if(obj->model->list[op])
        {
            ret = obj->model->list[op](obj, arg);
        }
        else if(obj->model->list[EVO_E(RELAY)])
        {
            ret = obj->model->list[EVO_E(RELAY)](obj,(void *)&(const EVO_T(RELAY)){.op = op,.arg = arg});
        }
        else if(obj->model->parent)
        {
            ret = ev_call_model_fun( obj, obj->model->parent, op, arg);
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

