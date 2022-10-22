
#include "./core/ev_core.h"
#include "./obj/common/ev_adp.h"
#include "edev_config.h"

EV_MODEL_FUN_DEF(ev_adp_m,RELAY)
{
    EV_MODEL_FUN_GET_ARG(ev_adp_m,RELAY);

    if(attr->obj && (*attr->obj))
    {
        __ev_do((*attr->obj),arg->op,arg->arg);
    }
    return 0;
}

EV_MODEL_FUN_DEF(ev_adp_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_adp_m,HELP);
/*

    const ev_obj_t adp = _ev_obj_forge(ev_adp_m,
                                         ev_adp_add_list(&obj1,&obj2 ...) 
                                         );
*/
    return 0;
}


EV_MODEL_FUN_DEF(ev_adp_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_adp_m,INIT);

    for(int i = 0; i < attr->list_len; i++)
    {
        if(attr->list[i])
        {
            if(_ev_do(attr->list[i],INIT) == 0)
            {
                (*attr->obj) = attr->list[i];
                return 0;
            }
        }
    }

    return 1;
}

EV_MODEL_FUN_DEF(ev_adp_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_adp_m,UNINIT);

    if(attr->obj && (*attr->obj))
    {
        _ev_do((*attr->obj),UNINIT);
        (*attr->obj) = 0;
    }

    return 1;
}

EV_MODEL_LIST_DEF(ev_adp_m,RELAY,HELP,INIT);
const ev_model_t ev_adp_m = EV_MODEL_DEF(ev_adp_m);
