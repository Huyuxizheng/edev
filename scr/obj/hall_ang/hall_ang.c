#include "./obj/hall_ang/hall_ang.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_hall_ang_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_hall_ang_m,HELP);
/*
                                   
*/

    return 0;
}


EV_MODEL_FUN_DEF(ev_hall_ang_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_hall_ang_m,INIT);


    if(attr->ic)
    {
        return _ev_obj_fun(attr->ic,INIT);   
    }

    return 1;
}


EV_MODEL_FUN_DEF(ev_hall_ang_m,HALL_ANG_GET)
{
    EV_MODEL_FUN_GET_ARG(ev_hall_ang_m,HALL_ANG_GET);


    if(attr->ic)
    {
        return _ev_obj_fun(attr->ic,HALL_ANG_GET,arg->out);   
    }

    return 1;
}


EV_MODEL_FUN_DEF(ev_hall_ang_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_hall_ang_m,UNINIT);

    if(attr->ic)
    {
        return _ev_obj_fun(attr->ic,UNINIT);   
    }

    return 1;
}


EV_MODEL_LIST_DEF(ev_hall_ang_m,HELP,INIT,HALL_ANG_GET,UNINIT);

const ev_model_t ev_hall_ang_m = EV_MODEL_DEF(ev_hall_ang_m);






