
#include "./dev/led/ev_led.h"
#include "./dri/ev_dri_gpio.h"

#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_led_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_led_type,LINK);
/*
    //创建led 的 gpio驱动
    ev_drive_s *led_gpio = ev_drive_forge(GPIO, 
                                            .group = GPIOA,
                                            .pin   = PIN_1,
                                            .set   = gpio_set,
                                            .togle = gpio_togle,
                                        );
    //创建LED设备
    ev_obj_s *led_dev = ev_obj_forge(ev_led_type,
                                        .gpio = led_gpio,   //LED设备增加gpio驱动
                                        .en_val = 1,        //设置LED引脚高电平为点亮
                                        );

    //设置LED
    ev_obj_fun(led_dev, LED_SET, 1);  

    //反转LED
    ev_obj_fun(led_dev, LED_TOGLE, 0);                                       
*/

    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,POWER)
{
    EV_TYPE_FUN_GET_ARG(ev_led_type,POWER);

    if(attr->gpio)
    {
        switch(arg->evp)
        {
            case EVP_NONE:case EVP_HIGH:case EVP_OPEN:
                //ev_dri_gpio_init(attr->gpio);
            break;
            case EVP_IDLE:case EVP_CLOSE:
                //ev_dri_gpio_uninit(attr->gpio);
            break;
        }

        return 0;
    }

    return 0;
}
EV_TYPE_FUN_DEF(ev_led_type,LED_SET)
{
    EV_TYPE_FUN_GET_ARG(ev_led_type,LED_SET);
    if(attr->gpio)
    {
        if(arg->state)
        {
            //ev_dri_gpio_set(attr->gpio,attr->en_val);
        }
        else
        {
            //ev_dri_gpio_set(attr->gpio,!attr->en_val);
        }
    }
    return 0;
}

EV_TYPE_FUN_DEF(ev_led_type,LED_SET_EN_VAL)
{
    EV_TYPE_FUN_GET_ARG(ev_led_type,LED_SET_EN_VAL);

    if(attr->gpio)
    {
            //ev_dri_gpio_togle(attr->gpio);
    }

    return 0;
}

EV_TYPE_LIST_DEF(ev_led_type,HELP,POWER,LED_SET);

const ev_type_t ev_led_type = EV_TYPE_DEF(ev_led_type);
