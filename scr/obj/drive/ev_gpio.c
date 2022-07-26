
#include "./obj/drive/ev_gpio.h"

#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_gpio_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,HELP);
/*
);                                       
*/

    return 0;
}


// // state IO口要设置的状态
// EV_FUN_DEF(GPIO_SET,uint8_t val);

// //EVD_LED_TOGGLE
// EV_FUN_DEF(GPIO_GET,uint8_t null);


// EV_FUN_DEF(GPIO_INIT_OUT,uint8_t null);

// EV_FUN_DEF(GPIO_INIT_IN,uint8_t null);

// EV_FUN_DEF(GPIO_INIT_INT,uint8_t null);
// EV_FUN_DEF(GPIO_INT_CB,uint8_t null);

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_SET)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_SET);
/*
);                                       
*/

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_GET)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_GET);
/*
);                                       
*/

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_INIT_IN)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_INIT_IN);
/*
);                                       
*/

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_INT_CB)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_INT_CB);
/*
);                                       
*/

    return 0;
}
EV_TYPE_LIST_DEF(ev_gpio_type,HELP);

const ev_type_t ev_gpio_type = EV_TYPE_DEF(ev_gpio_type);
