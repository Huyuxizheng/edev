#ifndef __EDEV_DRI_IRQ_H__
#define __EDEV_DRI_IRQ_H__
#include "./dri/ev_dri.h"


enum {
    EV_DRI_GPIO_INT_OUT_MODE,
    EV_DRI_GPIO_INT_IN_MODE,
    EV_DRI_GPIO_INT_INTERRUPT_MODE,
};

typedef struct{
    //可选的 GPIO组
    void*      group;
    //可选的 GPIO pin脚编号
    uint32_t    pin;
    //获得电平
    void        (*init)(void* group,uint32_t pin,uint8_t mode);
    //设置电平
    void        (*set_cb)(void* group,uint32_t pin,ev_obj_cb_t cb,void *param);
    //设置电平
    void        (*set)(void* group,uint32_t pin,uint8_t val);
    //获得电平
    uint8_t     (*get)(void* group,uint32_t pin);
    //获得电平
    void        (*uninit)(void* group,uint32_t pin);
}const EV_DRI_T(GPIO_INT);


inline void ev_dri_gpio_int_init(EV_DRI_T(GPIO_INT) *gpio_int,uint8_t mode){
    if(gpio_int&&gpio_int->init)
        gpio_int->init(gpio_int->group,gpio_int->pin,mode);
}
inline void ev_dri_gpio_int_set_cb(EV_DRI_T(GPIO_INT) *gpio_int,ev_obj_cb_t cb,void *param){
    if(gpio_int&&gpio_int->set_cb)
        gpio_int->set_cb(gpio_int->group,gpio_int->pin,cb,param);
}
inline void ev_dri_gpio_int_set(EV_DRI_T(GPIO_INT) *gpio_int,uint8_t val){
    if(gpio_int&&gpio_int->set)
        gpio_int->set(gpio_int->group,gpio_int->pin,val);
}
inline uint8_t ev_dri_gpio_int_get(EV_DRI_T(GPIO_INT) *gpio_int){
    if(gpio_int&&gpio_int->get)
        return gpio_int->get(gpio_int->group,gpio_int->pin);
    return 0;
}
inline void ev_dri_gpio_int_uninit(EV_DRI_T(GPIO_INT) *gpio_int){
    if(gpio_int&&gpio_int->uninit)
        gpio_int->uninit(gpio_int->group,gpio_int->pin);
}

#endif
