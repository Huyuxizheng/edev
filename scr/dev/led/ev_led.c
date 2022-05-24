#include "./dev/led/ev_led.h"


EV_TYPE_FUN_DEF(ev_led_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(HELP);

    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,LINK)
{
    EV_TYPE_FUN_GET_ARG(LINK);

    if(ev_dri_e_check(GPIO,arg->drive) == 0)
    {
        EV_DRI_S(GPIO) *gpio = arg->drive->p;
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_led_type,LED_SET)
{
    EV_TYPE_FUN_GET_ARG(LED_SET);
    
    arg->state = 0;
    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,LED_TOGLE)
{
    EV_TYPE_FUN_GET_ARG(LED_TOGLE);

    return 0;
}

static const edev_obj_fun_t EV_TYPE_LIST(ev_led_type)[] ={
    EV_TYPE_LIST_ADD_FUN(ev_led_type,HELP),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,LINK),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,LED_SET),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,LED_TOGLE),
};


const ev_type_s ev_led_type = {
    .name = "ev_led_type",
    .vals_create = 0,
    .vals_free = 0,

    .total = EV_TYPE_TOTAL(ev_led_type),
    .list  = EV_TYPE_LIST(ev_led_type),
};







