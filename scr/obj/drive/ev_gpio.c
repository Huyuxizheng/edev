
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


EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_SET)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_SET);

    if(attr->set)
    {
        attr->set(attr->group,attr->pin,arg->val);
    }

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
