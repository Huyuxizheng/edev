#ifndef __EDEV_HALL_ANG_H__
#define __EDEV_HALL_ANG_H__



#include "./core/ev_core.h"

enum{
    EVO_E(HALL_ANG_GET) = EVO_E(START),
};

//HALL_ANG_GET
EV_FUN_DEF(HALL_ANG_GET,float *angle);


typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *ic;
}EVO_ATTR_T(ev_hall_ang_m);
#define ev_hall_ang_m_attr_init 

extern const ev_model_t ev_hall_ang_m;


#endif