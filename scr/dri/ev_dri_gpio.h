#ifndef __EDEV_DRI_GPIO_H__
#define __EDEV_DRI_GPIO_H__
#include "./dri/ev_dri.h"


typedef struct{
    //可选的 GPIO组
    uint32_t    group;
    //可选的 GPIO pin脚编号
    uint32_t    pin;
    //获得电平
    void        (*init)(uint32_t group,uint32_t pin);
    //设置电平
    void        (*set)(uint32_t group,uint32_t pin,uint8_t val);
    //获得电平
    uint8_t     (*get)(uint32_t group,uint32_t pin);
    //反转电平
    void        (*togle)(uint32_t group,uint32_t pin);
    //获得电平
    void        (*uninit)(uint32_t group,uint32_t pin);
}const EV_DRI_T(GPIO);


inline void ev_dri_gpio_init(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->init)
        gpio->init(gpio->group,gpio->pin);
}
inline void ev_dri_gpio_set(EV_DRI_T(GPIO) *gpio,uint8_t val){
    if(gpio&&gpio->set)
        gpio->set(gpio->group,gpio->pin,val);
}
inline uint8_t ev_dri_gpio_get(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->get)
        return gpio->get(gpio->group,gpio->pin);
    return 0;
}
inline void ev_dri_gpio_togle(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->togle)
        gpio->togle(gpio->group,gpio->pin);
}
inline void ev_dri_gpio_uninit(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->uninit)
        gpio->uninit(gpio->group,gpio->pin);
}

#endif
