#ifndef __EDEV_TP_H__
#define __EDEV_TP_H__

/*
触摸驱动
*/


#include "./core/ev_core.h"

enum{
    EVO_E(TP_GET) = EVO_E(STARE),
};

//支持TP设备的子设备
enum{
    //EVO_E(SET_CB),    触摸按下回调
    //EVO_E(ADAPT),     自适应
    //EVO_E(SUPPORT),   设备支持检查
    EVO_E(TP_IC_GET) = EVO_E(STARE),//获得触摸数据
};

//EVD_TP_GET
typedef struct{
    uint16_t x;
    uint16_t y;
    uint32_t tick;
    uint8_t  statie;
}EVO_T(TP_GET_OUT);

typedef struct {
    EVO_T(TP_GET_OUT) *out;
}EVO_T(TP_GET);

typedef struct {
    EVO_T(TP_GET_OUT) *out;
}EVO_T(TP_IC_GET);

extern const ev_type_t ev_tp_type;





#endif
