#ifndef __EDEV_DRI_H__
#define __EDEV_DRI_H__

typedef const void * ev_dri_type;

#define EV_DRI_E(DRI) EV_DRI_##DRI##_E
#define EV_DRI_S(DRI) const EV_DRI_##DRI##_S
  
#define EV_DRI_DEF(DRI, ...)  &(const EV_DRI_S(DRI)[]){{__VA_ARGS__}}

#define _ev_drive_forge(DRI, ...)  (ev_drive_s *)&(const ev_drive_s []){{.e = EV_DRI_E(DRI),.p = EV_DRI_DEF(DRI, __VA_ARGS__)}}  


enum{
    EV_DRI_E(BASE) = 1,
    EV_DRI_E(GPIO),
    EV_DRI_E(SPI),
    EV_DRI_E(IIC),
};

typedef uint16_t ev_dri_e;

typedef struct{
    ev_dri_e       e;//枚举标识符
    ev_dri_type    p;
}ev_drive_s;

//判断类型-错误返回1
#define ev_dri_e_check(DRI_E,dri) \
((dri)->e != EV_DRI_E(DRI_E))


typedef struct{
    uint8_t   no_arg;
}EV_DRI_S(BASE);


#include "./dri/ev_dri_gpio.h"

typedef struct{
    uint8_t   no_arg;
}EV_DRI_S(SPI);


#endif
