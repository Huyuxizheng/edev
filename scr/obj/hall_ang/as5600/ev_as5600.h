#ifndef __EDEV_AS5600_H__
#define __EDEV_AS5600_H__



#include "./core/ev_core.h"



typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *i2c;
}EVO_ATTR_T(ev_as5600_m);
#define ev_as5600_m_attr_init 

extern const ev_model_t ev_as5600_m;


#endif