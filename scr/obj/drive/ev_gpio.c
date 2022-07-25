
#include "./obj/drive/ev_gpio.h"

#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_gpio_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_led_type,LINK);
/*
);                                       
*/

    return 0;
}


EV_TYPE_LIST_DEF(ev_gpio_type,HELP);

const ev_type_t ev_gpio_type = EV_TYPE_DEF(ev_gpio_type);
