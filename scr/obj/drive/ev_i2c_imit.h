#ifndef __EDEV_I2C_IMIT_H__
#define __EDEV_I2C_IMIT_H__


#include "./core/ev_core.h"
#include "./obj/drive/ev_i2c.h"




extern const ev_type_t ev_i2c_imit_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
}EVO_ATTR_T(ev_i2c_imit_type);
#define ev_i2c_imit_type_attr_init 

#endif
