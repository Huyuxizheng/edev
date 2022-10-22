#include "./obj/tp/ev_tp.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_tp_cap_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_tp_cap_m,HELP);
/*
                                   
*/

    return 0;
}


EV_MODEL_FUN_DEF(ev_tp_cap_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_tp_cap_m,INIT);


    if(attr->ic)
    {
        return _ev_do(attr->ic,INIT);   
    }

    return 1;
}


EV_MODEL_FUN_DEF(ev_tp_cap_m,TP_GET)
{
    EV_MODEL_FUN_GET_ARG(ev_tp_cap_m,TP_GET);


    if(attr->ic)
    {
        return _ev_do(attr->ic,TP_GET,arg->out);   
    }

    return 1;
}


EV_MODEL_FUN_DEF(ev_tp_cap_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_tp_cap_m,UNINIT);

    if(attr->ic)
    {
        return _ev_do(attr->ic,UNINIT);   
    }

    return 1;
}


EV_MODEL_LIST_DEF(ev_tp_cap_m,HELP,INIT,TP_GET,UNINIT);

const ev_model_t ev_tp_cap_m = EV_MODEL_DEF(ev_tp_cap_m);






