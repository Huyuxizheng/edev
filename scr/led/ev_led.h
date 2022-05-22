#ifndef __EDEV_CONFIG_H__
#define __EDEV_CONFIG_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"

enum{
    EVD_LED_SET = EVO_STARE,
    EVD_LED_TOGGLE,
};

//EVD_LED_SET
typedef struct {
    uint8_t state;// 1为点亮 0为熄灭
}EVO_S(EVD_LED_SET);

//EVD_LED_TOGGLE
typedef struct {
    uint8_t no_arg;//无参
}EVO_S(EVD_LED_TOGGLE);

extern const ev_type_s ev_led_type;

#endif
