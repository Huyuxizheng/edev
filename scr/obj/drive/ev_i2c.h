#ifndef __EDEV_I2C_H__
#define __EDEV_I2C_H__


#include "./core/ev_core.h"


enum{//独有方法列表
    EVO_E(I2C_INIT) = EVO_E(START),
    EVO_E(I2C_WRITE),
    EVO_E(I2C_READ),
    EVO_E(I2C_MEM_WRITE),
    EVO_E(I2C_MEM_READ)
};


EV_FUN_DEF(I2C_INIT,uint32_t max_khz);

EV_FUN_DEF(I2C_WRITE,uint8_t addr,const uint8_t *data,uint32_t size,uint8_t no_stop);

EV_FUN_DEF(I2C_READ,uint8_t addr,uint8_t *data,uint32_t size,uint8_t no_stop);


EV_FUN_DEF(I2C_MEM_WRITE,uint8_t addr,uint16_t mem_addr,uint16_t mem_addr_size,const uint8_t *data,uint32_t size);

EV_FUN_DEF(I2C_MEM_READ,uint8_t addr,uint16_t mem_addr,uint16_t mem_addr_size,uint8_t *data,uint32_t size);



extern const ev_model_t ev_i2c_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    //可选的 I2C句柄
    void*       handle;
    //获得电平
    uint8_t     (*init)(void* handle,uint32_t max_khz);
    //设置电平
    uint8_t     (*write)(void* handle,uint8_t addr,const uint8_t *dat,uint16_t len,uint8_t no_stop);
    //获得电平
    uint8_t     (*read)(void* handle,uint8_t addr,uint8_t *dat,uint16_t len,uint8_t no_stop);
    //获得电平
    void        (*uninit)(void* handle);

}EVO_ATTR_T(ev_i2c_m);
#define ev_i2c_m_attr_init 

#endif
