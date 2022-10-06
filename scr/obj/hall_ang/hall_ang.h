#ifndef __EDEV_HALL_ANG_H__
#define __EDEV_HALL_ANG_H__



#include "./core/ev_core.h"

enum{
    EVO_E(HALL_ANG_GET) = EVO_E(START),
};

//EVD_TP_GET
typedef struct{
    float angle;
}ev_hall_ang_get_out;
EV_FUN_DEF(HALL_ANG_GET,ev_hall_ang_get_out *out);


typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *ic;
}EVO_ATTR_T(ev_hall_ang_m);
#define ev_hall_ang_m_attr_init 

extern const ev_model_t ev_hall_ang_m;


#endif