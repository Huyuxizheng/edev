
#include "./core/ev_core.h"
#include "./obj/led/ev_led.h"
#include "./obj/drive/ev_gpio.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_led_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_led_m,HELP);
/*
    //创建led 的 gpio驱动
    ev_drive_s *led_gpio = ev_obj_forge(GPIO, 
                                            .group = GPIOA,
                                            .pin   = PIN_1,
                                            .set   = gpio_set,
                                            .togle = gpio_togle,
                                        );
    //创建LED设备
    ev_obj_s *led_dev = ev_obj_forge(ev_led_m,
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


EV_MODEL_FUN_DEF(ev_led_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_led_m,INIT);

    if(attr->gpio)
    {
        
        _ev_obj_fun(attr->gpio, GPIO_INIT,EV_GPIO_MODE_OUT);  
        return 0;
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_led_m,LED_SET)
{
    EV_MODEL_FUN_GET_ARG(ev_led_m,LED_SET);
    if(attr->gpio)
    {
        if(arg->state)
        {
            _ev_obj_fun(attr->gpio, GPIO_SET,attr->en_val);
        }
        else
        {
            _ev_obj_fun(attr->gpio, GPIO_SET,!attr->en_val);
        }
    }
    return 0;
}


EV_MODEL_FUN_DEF(ev_led_m,LED_TOGLE)
{
    EV_MODEL_FUN_GET_ARG(ev_led_m,LED_TOGLE);
    if(attr->gpio)
    {
         _ev_obj_fun(attr->gpio, GPIO_TOGLE);
    }
    return 0;
}


EV_MODEL_LIST_DEF(ev_led_m,HELP,INIT,LED_SET,LED_TOGLE);

const ev_model_t ev_led_m = EV_MODEL_DEF(ev_led_m);
