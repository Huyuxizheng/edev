#ifndef __EDEV_GPIO_H__
#define __EDEV_GPIO_H__



#include "./core/ev_core.h"
enum{
    EV_GPIO_MODE_OUT = 0,
    EV_GPIO_MODE_IN,
    EV_GPIO_MODE_OD,
    EV_GPIO_MODE_ISR_UP,
    EV_GPIO_MODE_ISR_DOWN,
};
typedef uint8_t ev_gpio_mode_e;

enum{//独有方法列表
    EVO_E(GPIO_INIT) = EVO_E(INIT),
    EVO_E(GPIO_SET) = EVO_E(START),
    EVO_E(GPIO_TOGLE),
    EVO_E(GPIO_GET)
};


//IO口要设置的状态
EV_FUN_DEF(GPIO_SET,uint8_t val);
EV_FUN_DEF(GPIO_TOGLE);
EV_FUN_DEF(GPIO_GET);
EV_FUN_DEF(GPIO_INIT,ev_gpio_mode_e mode);



extern const ev_model_t ev_gpio_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头    //可选的 GPIO组

    //可选的 GPIO pin脚编号
    void*    group;
    uint32_t    pin;

    //初始化
    uint8_t        (*init)(void* group,uint32_t pin,ev_gpio_mode_e mode,void (*gpio_isr)(void *param),void *param);
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

}EVO_ATTR_T(ev_gpio_m);
#define ev_gpio_m_attr_init 

#endif
