#ifndef __EDEV_I2C_H__
#define __EDEV_I2C_H__


#include "./core/ev_core.h"


enum{//独有方法列表
    EVO_E(I2C_WRITE) = EVO_E(STARE),

};







extern const ev_type_t ev_i2c_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    //可选的 I2C句柄
    void*       handle;
    //获得电平
    void        (*init)(void* handle);
    //设置电平
    uint8_t     (*write)(void* handle,uint8_t addr,uint8_t *dat,uint16_t len);
    //获得电平
    uint8_t     (*read)(void* handle,uint8_t addr,uint8_t *dat,uint16_t len);
    //获得电平
    void        (*uninit)(void* handle);

}EVO_ATTR_T(ev_i2c_type);
#define ev_i2c_type_attr_init 

#endif
