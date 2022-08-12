#ifndef __EDEV_TP_H__
#define __EDEV_TP_H__

/*
触摸驱动
*/


#include "./core/ev_core.h"

enum{
    EVO_E(TP_GET) = EVO_E(START),
};

//EVD_TP_GET
typedef struct{
    uint16_t x;
    uint16_t y;
    uint32_t tick;
    uint8_t  state;
}ev_tp_get_out;
EV_FUN_DEF(TP_GET,ev_tp_get_out *out);


typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *ic;
}EVO_ATTR_T(ev_tp_cap_type);
#define ev_tp_cap_type_attr_init 

extern const ev_type_t ev_tp_cap_type;


#endif
