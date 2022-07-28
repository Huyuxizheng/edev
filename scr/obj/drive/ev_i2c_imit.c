﻿
#include "./core/ev_core.h"

#include "./obj/drive/ev_i2c_imit.h"
#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_i2c_imit_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,HELP);
/*
    //创建led 的 gpio驱动
    ev_drive_s *led_gpio = ev_obj_forge(GPIO, 
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


EV_TYPE_FUN_DEF(ev_i2c_imit_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,INIT);



    return 0;
}



EV_TYPE_LIST_DEF(ev_i2c_imit_type,HELP,INIT);

const ev_type_t ev_i2c_imit_type = EV_TYPE_DEF(ev_i2c_imit_type);
