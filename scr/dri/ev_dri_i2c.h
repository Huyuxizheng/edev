#ifndef __EDEV_DRI_I2C_H__
#define __EDEV_DRI_I2C_H__
#include "./dri/ev_dri.h"


typedef struct{
    //可选的 SPI句柄
    void*       handle;
    //获得电平
    void        (*init)(void* handle);
    //设置电平
    uint8_t     (*write)(void* handle,uint8_t addr,uint8_t *dat,uint16_t len);
    //获得电平
    uint8_t     (*read)(void* handle,uint8_t addr,uint8_t *dat,uint16_t len);
    //获得电平
    void        (*uninit)(void* handle);
}const EV_DRI_T(I2C);

inline void ev_dri_i2c_init(EV_DRI_T(I2C) *i2c){
    if(i2c&&i2c->init)
        i2c->init(i2c->handle);
}
inline uint8_t ev_dri_i2c_write(EV_DRI_T(I2C) *i2c,uint8_t addr,uint8_t *dat,uint16_t len){
    if(i2c&&i2c->write)
        return i2c->write(i2c->handle,addr,dat,len);
    return 0;
}
inline uint8_t ev_dri_i2c_read(EV_DRI_T(I2C) *i2c,uint8_t addr,uint8_t *dat,uint16_t len){
    if(i2c&&i2c->read)
        return i2c->read(i2c->handle,addr,dat,len);
    return 0;
}
inline void ev_dri_i2c_uninit(EV_DRI_T(I2C) *i2c){
    if(i2c&&i2c->uninit)
        i2c->uninit(i2c->handle);
}
#endif