
#include "./core/ev_core.h"
#include "./obj/common/ev_adp.h"
#include "edev_config.h"

EV_TYPE_FUN_DEF(ev_adp_type,RELAY)
{
    EV_TYPE_FUN_GET_ARG(ev_adp_type,RELAY);

    if(attr->obj && (*attr->obj))
    {
        __ev_obj_fun((*attr->obj),arg->op,arg->arg);
    }
    return 0;
}

EV_TYPE_FUN_DEF(ev_adp_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_adp_type,HELP);
/*

    const ev_obj_t adp = _ev_obj_forge(ev_adp_type,
                                         ev_adp_add_list(&obj1,&obj2 ...) 
                                         );
*/
    return 0;
}


EV_TYPE_FUN_DEF(ev_adp_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_adp_type,INIT);

    for(int i = 0; i < attr->list_len; i++)
    {
        if(attr->list[i])
        {
            if(_ev_obj_fun(attr->list[i],INIT) == 0)
            {
                (*attr->obj) = attr->list[i];
                return 0;
            }
        }
    }

    return 1;
}

EV_TYPE_FUN_DEF(ev_adp_type,UNINIT)
{
    EV_TYPE_FUN_GET_ARG(ev_adp_type,UNINIT);

    if(attr->obj && (*attr->obj))
    {
        _ev_obj_fun((*attr->obj),UNINIT);
        (*attr->obj) = 0;
    }

    return 1;
}

EV_TYPE_LIST_DEF(ev_adp_type,RELAY,HELP,INIT);
const ev_type_t ev_adp_type = EV_TYPE_DEF(ev_adp_type);
