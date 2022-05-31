#ifndef __EDEV_DRI_H__
#define __EDEV_DRI_H__
#include "stdint.h"

typedef void (*ev_obj_cb_t)(void *param,uint16_t event,void *arg);

typedef const void * ev_dri_type;

#define EV_DRI_E(DRI) EV_DRI_##DRI##_E
#define EV_DRI_T(DRI) EV_DRI_##DRI##_T
  
#define EV_DRI_DEF(DRI, ...)  &(const EV_DRI_T(DRI)[]){{__VA_ARGS__}}

#define _ev_drive_forge(DRI, ...)  (ev_drive_t *)&(ev_drive_t []){{.e = EV_DRI_E(DRI),.p = EV_DRI_DEF(DRI, __VA_ARGS__)}}  


enum{
    EV_DRI_E(BASE) = 1,
    EV_DRI_E(GPIO),
    EV_DRI_E(GPIO_INT),
    EV_DRI_E(SPI),
    EV_DRI_E(I2C),
};

typedef uint16_t ev_dri_e;

typedef struct{
    ev_dri_e       e;//枚举标识符
    ev_dri_type    p;
}const ev_drive_t;

//判断类型-错误返回1
#define ev_dri_e_check(DRI_E,dri) \
((dri)->e != EV_DRI_E(DRI_E))


typedef struct{
    uint8_t   no_arg;
}EV_DRI_T(BASE);


#include "./dri/ev_dri_gpio.h"

#include "./dri/ev_dri_i2c.h"

#include "./dri/ev_dri_gpio_int.h"

#include "./dri/ev_dri_spi.h"

#endif
