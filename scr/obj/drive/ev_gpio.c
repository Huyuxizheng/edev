
#include "./obj/drive/ev_gpio.h"

#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_gpio_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,HELP);
/*
                                      
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

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_TOGLE)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_TOGLE);

    if(attr->togle)
    {
        attr->togle(attr->group,attr->pin);
    }
    else if(attr->set && attr->get)
    {
        attr->set(attr->group,attr->pin,!attr->get(attr->group,attr->pin));
    }

    return 0;
}
EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_GET)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_GET);

    if(attr->get)
    {
        return attr->get(attr->group,attr->pin);
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_INIT_IN)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_INIT_IN);

    if(attr->init_in)
    {
        return attr->init_in(attr->group,attr->pin);
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_INIT_OUT)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_INIT_OUT);

    if(attr->init_out)
    {
        return attr->init_out(attr->group,attr->pin);
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_INIT_OD)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_INIT_OD);

    if(attr->init_od)
    {
        return attr->init_od(attr->group,attr->pin);
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_gpio_type,GPIO_INIT_ISR)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,GPIO_INIT_ISR);

    if(attr->init_isr)
    {
        return attr->init_isr(attr->group,attr->pin,arg->gpio_isr,arg->param);
    }

    return 0;
}
EV_TYPE_FUN_DEF(ev_gpio_type,UNINIT)
{
    EV_TYPE_FUN_GET_ARG(ev_gpio_type,UNINIT);

    if(attr->uninit)
    {
        attr->uninit(attr->group,attr->pin);
    }

    return 0;
}


EV_TYPE_LIST_DEF(ev_gpio_type,HELP,GPIO_SET,GPIO_TOGLE,GPIO_GET,GPIO_INIT_OUT,GPIO_INIT_IN,GPIO_INIT_OD,GPIO_INIT_ISR);
const ev_type_t ev_gpio_type = EV_TYPE_DEF(ev_gpio_type);
