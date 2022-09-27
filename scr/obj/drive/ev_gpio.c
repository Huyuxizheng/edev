
#include "./obj/drive/ev_gpio.h"

#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_gpio_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_gpio_m,HELP);
/*
                                      
*/

    return 0;
}

EV_MODEL_FUN_DEF(ev_gpio_m,GPIO_SET)
{
    EV_MODEL_FUN_GET_ARG(ev_gpio_m,GPIO_SET);

    if(attr->set)
    {
        attr->set(attr->group,attr->pin,arg->val);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_gpio_m,GPIO_TOGLE)
{
    EV_MODEL_FUN_GET_ARG(ev_gpio_m,GPIO_TOGLE);

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
EV_MODEL_FUN_DEF(ev_gpio_m,GPIO_GET)
{
    EV_MODEL_FUN_GET_ARG(ev_gpio_m,GPIO_GET);

    if(attr->get)
    {
        return attr->get(attr->group,attr->pin);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_gpio_m,GPIO_INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_gpio_m,GPIO_INIT);

    switch(arg->mode)
    {
        case EV_GPIO_MODE_OUT:
            if(attr->init_out){return attr->init_out(attr->group,attr->pin);}
        break;
        case EV_GPIO_MODE_IN:
            if(attr->init_in){return attr->init_in(attr->group,attr->pin);}
        break;
        case EV_GPIO_MODE_OD:
            if(attr->init_od){return attr->init_od(attr->group,attr->pin);}
        break;
        case EV_GPIO_MODE_ISR_UP:case EV_GPIO_MODE_ISR_DOWN:
            if(attr->init_isr){return attr->init_isr(attr->group,attr->pin,0,0);}
        break;
    }
    if(attr->init)
    {
        return attr->init(attr->group,attr->pin,arg->mode,0,0);
    }
    return 0;
}


EV_MODEL_FUN_DEF(ev_gpio_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_gpio_m,UNINIT);

    if(attr->uninit)
    {
        attr->uninit(attr->group,attr->pin);
    }

    return 0;
}


EV_MODEL_LIST_DEF(ev_gpio_m,HELP,GPIO_SET,GPIO_TOGLE,GPIO_GET,GPIO_INIT,UNINIT);
const ev_model_t ev_gpio_m = EV_MODEL_DEF(ev_gpio_m);
