#ifndef __EDEV_DRI_SPI_H__
#define __EDEV_DRI_SPI_H__
#include "./dri/ev_dri.h"


typedef struct{
    //可选的 SPI句柄
    void*       handle;
    //初始化
    void        (*init)(void* handle);
    //设置电平
    void        (*write)(void* handle);
    //获得电平
    uint8_t     (*read)(void* handle);
    //获得电平
    void        (*uninit)(void* handle);
}const EV_DRI_T(SPI);

inline void ev_dri_spi_init(EV_DRI_T(SPI) *spi){
    if(spi&&spi->init)
        spi->init(spi->handle);
}

#endif
