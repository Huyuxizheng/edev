#include "./led/ev_led.h"


EV_TYPE_FUN_DEF(ev_led_type,EVO_HELP)
{
    EV_TYPE_FUN_GET_ARG(EVO_HELP);

    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,EVO_LINK)
{
    EV_TYPE_FUN_GET_ARG(EVO_LINK);
    
    return 0;
}

EV_TYPE_FUN_DEF(ev_led_type,EVD_LED_SET)
{
    EV_TYPE_FUN_GET_ARG(EVD_LED_SET);
    
    arg->state = 0;
    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,EVD_LED_TOGGLE)
{
    EV_TYPE_FUN_GET_ARG(EVD_LED_TOGGLE);

    return 0;
}

static const edev_obj_fun_t EV_TYPE_LIST(ev_led_type)[] ={
    EV_TYPE_LIST_ADD_FUN(ev_led_type,EVO_HELP),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,EVO_LINK),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,EVD_LED_SET),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,EVD_LED_TOGGLE),
};


const ev_type_s ev_led_type = {
    .name = "ev_led_type",
    .vals_create = 0,
    .vals_free = 0,

    .total = EV_TYPE_TOTAL(ev_led_type),
    .list  = EV_TYPE_LIST(ev_led_type),
};














