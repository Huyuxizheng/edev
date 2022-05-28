#include "./dev/tp/ev_tp.h"
#include "edev_config.h"
#include "./core/ev_obj_list.h"

typedef struct{
    ev_obj_s        *obj;
    ev_obj_list_s   obj_list;
}ev_tp_vals_s;

EV_TYPE_FUN_DEF(ev_tp_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(HELP);
/*
                                   
*/

    return 0;
}


EV_TYPE_FUN_DEF(ev_tp_type,LINK)
{
    EV_TYPE_FUN_GET_ARG(LINK);
    if(!arg->obj){return 1;}
    ev_tp_vals_s *vals = self->vals;

    if(_ev_obj_fun(arg->obj,SUPPORT,self) == 1)
    {//如果对象支持
        if(ev_obj_list_add_obj_filter(&(vals->obj_list),arg->obj) == 0)
        {//如果注册成功增加持股
            _ev_obj_share_add(arg->obj,self);
        }
            
    }

    return 1;
}

EV_TYPE_FUN_DEF(ev_tp_type,POWER)
{
    EV_TYPE_FUN_GET_ARG(POWER);

    ev_tp_vals_s *vals = self->vals;

    if(!vals->obj){return 1;}//未自适应

    return 0;
}
EV_TYPE_FUN_DEF(ev_tp_type,TP_GET)
{
    EV_TYPE_FUN_GET_ARG(TP_GET);

    ev_tp_vals_s *vals = self->vals;

    if(!vals->obj){return 1;}//未自适应

    return 0;
}




static const edev_obj_fun_t EV_TYPE_LIST(ev_tp_type)[] ={
    EV_TYPE_LIST_ADD_FUN(ev_tp_type,HELP),
    EV_TYPE_LIST_ADD_FUN(ev_tp_type,LINK),
    EV_TYPE_LIST_ADD_FUN(ev_tp_type,POWER),
    EV_TYPE_LIST_ADD_FUN(ev_tp_type,TP_GET),
};
uint8_t ev_tp_type_vals_create(ev_obj_s *obj)
{
    obj->vals = ev_malloc(sizeof(ev_tp_vals_s));
    if(obj->vals)
    {
        ((ev_tp_vals_s *)obj->vals)->obj = 0;
        ((ev_tp_vals_s *)obj->vals)->obj_list.next = 0;
        return 0;
    }
    else
    {
        return 1;
    }
}
//自变量释放方法
void ev_tp_type_vals_free(ev_obj_s *obj)
{
    if(obj->vals)
    {
        ev_free(obj->vals);
    }
}

const ev_type_s ev_tp_type = {
    .name = "ev_tp_type",
    .vals_create = ev_tp_type_vals_create,
    .vals_free = ev_tp_type_vals_free,

    .total = EV_TYPE_TOTAL(ev_tp_type),
    .list  = EV_TYPE_LIST(ev_tp_type),
};






