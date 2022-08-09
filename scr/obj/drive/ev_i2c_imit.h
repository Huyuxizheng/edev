#ifndef __EDEV_I2C_IMIT_H__
#define __EDEV_I2C_IMIT_H__


#include "./core/ev_core.h"
#include "./obj/drive/ev_i2c.h"


extern const ev_type_t ev_i2c_imit_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    uint8_t            *t;//默认t==5 100KHZ
    const ev_obj_t*  sda;
    const ev_obj_t*  scl;
}EVO_ATTR_T(ev_i2c_imit_type);
#define ev_i2c_imit_type_attr_init .t = EV_TO_RAM(uint8_t,5),

#endif
