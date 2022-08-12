#ifndef __EDEV_LED_H__
#define __EDEV_LED_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"

enum{//方法列表
    EVO_E(LED_SET) = EVO_E(START),
    EVO_E(LED_TOGLE),
};


//EVD_LED_SET
//     uint8_t state;// 1为点亮 0为熄灭
EV_FUN_DEF(LED_SET,uint8_t state);

//EVD_LED_TOGGLE
//uint8_t no_arg;//无参
EV_FUN_DEF(LED_TOGLE);


extern const ev_type_t ev_led_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *gpio;
    uint8_t             en_val;
}EVO_ATTR_T(ev_led_type);
#define ev_led_type_attr_init 

#endif
