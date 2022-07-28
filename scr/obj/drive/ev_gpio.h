#ifndef __EDEV_GPIO_H__
#define __EDEV_GPIO_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"

enum{//独有方法列表
    EVO_E(GPIO_SET) = EVO_E(STARE),
    EVO_E(GPIO_TOGLE),
    EVO_E(GPIO_GET),
    EVO_E(GPIO_INIT_OUT),
    EVO_E(GPIO_INIT_OD),
    EVO_E(GPIO_INIT_IN),
    EVO_E(GPIO_INIT_ISR),
    EVO_E(GPIO_ISR_CB),
};


//IO口要设置的状态
EV_FUN_DEF(GPIO_SET,uint8_t val);
EV_FUN_DEF(GPIO_TOGLE);
EV_FUN_DEF(GPIO_GET);
EV_FUN_DEF(GPIO_INIT_OUT);
EV_FUN_DEF(GPIO_INIT_IN);
EV_FUN_DEF(GPIO_INIT_OD);
EV_FUN_DEF(GPIO_INIT_ISR,void (*gpio_isr)(void *param),void *param);


extern const ev_type_t ev_gpio_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头    //可选的 GPIO组

    //可选的 GPIO pin脚编号
    void*    group;
    uint32_t    pin;

    //初始化
    uint8_t        (*init_out)(void* group,uint32_t pin);
    uint8_t        (*init_in)(void* group,uint32_t pin);
    uint8_t        (*init_od)(void* group,uint32_t pin);
    uint8_t        (*init_isr)(void* group,uint32_t pin,void (*gpio_isr)(void *param),void *param);
    //反初始化
    void           (*uninit)(void* group,uint32_t pin);

    //设置电平
    void        (*set)(void* group,uint32_t pin,uint8_t val);
    void        (*togle)(void* group,uint32_t pin);
    //获得电平
    uint8_t     (*get)(void* group,uint32_t pin);

}EVO_ATTR_T(ev_gpio_type);
#define ev_gpio_type_attr_init 

#endif
