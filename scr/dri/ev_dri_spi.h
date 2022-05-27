﻿#ifndef __EDEV_DRI_SPI_H__
#define __EDEV_DRI_SPI_H__
#include "./dri/ev_dri.h"


typedef struct{
    //可选的 SPI句柄
    void*       handle;
    //初始化
    void        (*init)(void* handle,uint32_t pin);
    //设置电平
    void        (*set)(void* handle,uint32_t pin,uint8_t val);
    //获得电平
    uint8_t     (*get)(void* handle,uint32_t pin);
    //获得电平
    void        (*uninit)(void* handle,uint32_t pin);
}const EV_DRI_S(SPI);

inline void ev_dri_spi_init(EV_DRI_S(SPI) *spi){
    if(spi->init)
        spi->init(gpio->group,gpio->pin);
}

#endif