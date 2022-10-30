#ifndef __EDEV_SPI_H__
#define __EDEV_SPI_H__


#include "./core/ev_core.h"


enum{//独有方法列表
    EVO_E(SPI_WRITE) = EVO_E(WRITE),
    EVO_E(SPI_READ) = EVO_E(READ),
    EVO_E(SPI_INIT) = EVO_E(START),
};


enum{
    EV_SPI_MODE_1,//CPOL 0,CPHA 0
    EV_SPI_MODE_2,//CPOL 0,CPHA 1
    EV_SPI_MODE_3,//CPOL 1,CPHA 0
    EV_SPI_MODE_4,//CPOL 1,CPHA 1
};
typedef uint8_t ev_spi_mode_e;

EV_FUN_DEF(SPI_INIT,ev_spi_mode_e mode,uint32_t max_Mhz);

EV_FUN_DEF(SPI_WRITE,const uint8_t *data,uint32_t size);

EV_FUN_DEF(SPI_READ,uint8_t *data,uint32_t size);



extern const ev_model_t ev_spi_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    //句柄 内部变量
    void*       handle;
    //获得电平
    uint8_t     (*init)(void* handle,ev_spi_mode_e mode,uint32_t max_Mhz);
    //设置电平
    uint8_t     (*write)(void* handle,const uint8_t *dat,uint16_t len);
    //获得电平
    uint8_t     (*read)(void* handle,uint8_t *dat,uint16_t len);
    //获得电平
    void        (*uninit)(void* handle);

}EVO_ATTR_T(ev_spi_m);
#define ev_spi_m_attr_init  .handle = EV_TO_RAM(void*,0),

#endif

