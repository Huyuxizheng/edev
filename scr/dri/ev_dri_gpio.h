#ifndef __EDEV_DRI_GPIO_H__
#define __EDEV_DRI_GPIO_H__
#include "./dri/ev_dri.h"


typedef struct{
    //获得电平
    void        (*init)(void);
    //设置电平
    void        (*set)(uint8_t val);
    //获得电平
    uint8_t     (*get)(void);
    //反转电平
    void        (*togle)(void);
    //获得电平
    void        (*uninit)(void);
}const EV_DRI_T(GPIO);


static inline void ev_dri_gpio_init(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->init)
        gpio->init();
}
static inline void ev_dri_gpio_set(EV_DRI_T(GPIO) *gpio,uint8_t val){
    if(gpio&&gpio->set)
        gpio->set(val);
}
static inline uint8_t ev_dri_gpio_get(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->get)
        return gpio->get();
    return 0;
}
static inline void ev_dri_gpio_togle(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->togle)
        gpio->togle();
}
static inline void ev_dri_gpio_uninit(EV_DRI_T(GPIO) *gpio){
    if(gpio&&gpio->uninit)
        gpio->uninit();
}

#endif
