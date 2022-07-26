#ifndef __EDEV_ADP_H__
#define __EDEV_ADP_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"

enum{//方法列表
    EVO_E(LED_SET) = EVO_E(STARE),
    EVO_E(LED_TOGLE),
    EVO_E(LED_SET_EN_VAL),
};


//EVD_LED_SET
//     uint8_t state;// 1为点亮 0为熄灭
EV_FUN_DEF(LED_SET,uint8_t state);

//EVD_LED_TOGGLE
//uint8_t no_arg;//无参
EV_FUN_DEF(LED_TOGLE,uint8_t no_arg);

//EVD_LED_TOGGLE
//uint8_t en_val;//设置点亮的电平值
EV_FUN_DEF(LED_SET_EN_VAL,uint8_t en_val,uint8_t state);

extern const ev_type_t ev_led_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    ev_obj_t            *gpio;
    uint8_t             en_val;
}EVO_ATTR_T(ev_adp_type);
#define ev_led_type_attr_init 

#endif
