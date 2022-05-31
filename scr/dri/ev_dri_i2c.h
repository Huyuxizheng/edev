#ifndef __EDEV_DRI_I2C_H__
#define __EDEV_DRI_I2C_H__
#include "./dri/ev_dri.h"


typedef struct{
    //获得电平
    void        (*init)(void);
    //设置电平
    uint8_t     (*write)(uint8_t addr,const uint8_t *dat,uint16_t len);
    //获得电平
    uint8_t     (*read)(uint8_t addr,uint8_t *dat,uint16_t len);
    //获得电平
    void        (*uninit)(void);
}const EV_DRI_T(I2C);

static inline void ev_dri_i2c_init(EV_DRI_T(I2C) *i2c){
    if(i2c&&i2c->init)
        i2c->init();
}
static inline uint8_t ev_dri_i2c_write(EV_DRI_T(I2C) *i2c,uint8_t addr,const uint8_t *dat,uint16_t len){
    if(i2c&&i2c->write)
        return i2c->write(addr,dat,len);
    return 0;
}
static inline uint8_t ev_dri_i2c_read(EV_DRI_T(I2C) *i2c,uint8_t addr,uint8_t *dat,uint16_t len){
    if(i2c&&i2c->read)
        return i2c->read(addr,dat,len);
    return 0;
}
static inline void ev_dri_i2c_uninit(EV_DRI_T(I2C) *i2c){
    if(i2c&&i2c->uninit)
        i2c->uninit();
}
#endif