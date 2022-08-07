#include "./obj/tp/ev_tp.h"
#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_tp_cap_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_cap_type,HELP);
/*
                                   
*/

    return 0;
}


EV_TYPE_FUN_DEF(ev_tp_cap_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_cap_type,INIT);


    if(attr->ic)
    {
        return _ev_obj_fun(attr->ic,INIT);   
    }

    return 1;
}


EV_TYPE_FUN_DEF(ev_tp_cap_type,TP_GET)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_cap_type,TP_GET);


    if(attr->ic)
    {
        return _ev_obj_fun(attr->ic,TP_GET,arg->out);   
    }

    return 1;
}


EV_TYPE_FUN_DEF(ev_tp_cap_type,UNINIT)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_cap_type,UNINIT);

    if(attr->ic)
    {
        return _ev_obj_fun(attr->ic,UNINIT);   
    }

    return 1;
}


EV_TYPE_LIST_DEF(ev_tp_cap_type,HELP,INIT,TP_GET,UNINIT);

const ev_type_t ev_tp_cap_type = EV_TYPE_DEF(ev_tp_cap_type);






