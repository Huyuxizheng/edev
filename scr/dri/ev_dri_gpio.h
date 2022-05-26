﻿#ifndef __EDEV_DRI_GPIO_H__
#define __EDEV_DRI_GPIO_H__
#include "./dri/ev_dri.h"


typedef struct{
    //可选的 GPIO组
    uint32_t    group;
    //可选的 GPIO pin脚编号
    uint32_t    pin;
    //设置电平
    void        (*set)(uint32_t group,uint32_t pin,uint8_t val);
    //获得电平
    uint8_t     (*get)(uint32_t group,uint32_t pin);
    //反转电平
    void        (*togle)(uint32_t group,uint32_t pin);
}const EV_DRI_S(GPIO);
inline void ev_dri_gpio_set(EV_DRI_S(GPIO) *gpio,uint8_t val){
    if(gpio->set)
        gpio->set(gpio->group,gpio->pin,val);
}
inline uint8_t ev_dri_gpio_get(EV_DRI_S(GPIO) *gpio){
    if(gpio->get)
        return gpio->get(gpio->group,gpio->pin);
    return 0;
}
inline void ev_dri_gpio_togle(EV_DRI_S(GPIO) *gpio){
    if(gpio->togle)
        gpio->togle(gpio->group,gpio->pin);
}

#endif