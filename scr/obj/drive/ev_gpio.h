#ifndef __EDEV_GPIO_H__
#define __EDEV_GPIO_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"

enum{//方法列表
    EVO_E(GPIO_SET) = EVO_E(STARE),
    EVO_E(GPIO_GET),
    EVO_E(GPIO_INIT_OUT),
    EVO_E(GPIO_INIT_IN),
    EVO_E(GPIO_INIT_INT),
};



//     uint8_t state;// 1为点亮 0为熄灭
EV_FUN_DEF(GPIO_SET,uint8_t state);

//EVD_LED_TOGGLE
//uint8_t no_arg;//无参
EV_FUN_DEF(GPIO_GET,uint8_t no_arg);

//EVD_LED_TOGGLE
//uint8_t en_val;//设置点亮的电平值
EV_FUN_DEF(GPIO_INIT_OUT,uint8_t en_val,uint8_t state);

extern const ev_type_t ev_gpio_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头    //可选的 GPIO组
    uint32_t    group;
    //可选的 GPIO pin脚编号
    uint32_t    pin;
    //获得电平
    void        (*init)(uint32_t group,uint32_t pin,uint8_t mode);
    //设置电平
    void        (*set_cb)(uint32_t group,uint32_t pin,ev_obj_cb_t cb,void *param);
    //设置电平
    void        (*set)(uint32_t group,uint32_t pin,uint8_t val);
    //获得电平
    uint8_t     (*get)(uint32_t group,uint32_t pin);
    //获得电平
    void        (*uninit)(uint32_t group,uint32_t pin);
}EVO_ATTR_T(ev_gpio_type);
#define ev_gpio_type_attr_init 

#endif
