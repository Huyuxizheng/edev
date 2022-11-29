#ifndef __EDEV_SPI_H__
#define __EDEV_SPI_H__


#include "./core/ev_core.h"


enum{//独有方法列表
    EVO_E(SPI_INIT) = EVO_E(INIT),
    EVO_E(SPI_WRITE) = EVO_E(START),
    EVO_E(SPI_INIT_CS),
    EVO_E(SPI_READ),
    EVO_E(SPI_WRITE_THEN_WRITE),
    EVO_E(SPI_WRITE_THEN_READ),
    EVO_E(SPI_CMD),
    EVO_E(SPI_CMD_WRITE),
    EVO_E(SPI_CMD_READ),
    EVO_E(SPI_MEM_WRITE),
    EVO_E(SPI_MEM_READ),
};


enum{
    EV_SPI_MODE_0,//CPOL 0,CPHA 0
    EV_SPI_MODE_1,//CPOL 0,CPHA 1
    EV_SPI_MODE_2,//CPOL 1,CPHA 0
    EV_SPI_MODE_3,//CPOL 1,CPHA 1
};
typedef uint8_t ev_spi_mode_e;

EV_FUN_DEF(SPI_INIT,ev_spi_mode_e mode,uint32_t max_Mhz,const ev_obj_t *cs_io);

EV_FUN_DEF(SPI_INIT_CS,const ev_obj_t *cs_io);

EV_FUN_DEF(SPI_WRITE,const ev_obj_t *cs_io,const uint8_t *data,uint32_t size);

EV_FUN_DEF(SPI_READ,const ev_obj_t *cs_io,uint8_t *data,uint32_t size);

EV_FUN_DEF(SPI_WRITE_THEN_WRITE,const ev_obj_t *cs_io,const uint8_t *data1,uint32_t size1,const uint8_t *data2,uint32_t size2);

EV_FUN_DEF(SPI_WRITE_THEN_READ,const ev_obj_t *cs_io,uint8_t *data1,uint32_t size1,uint8_t *data2,uint32_t size2);


EV_FUN_DEF(SPI_CMD,const ev_obj_t *cs_io,uint32_t cmd,uint8_t cmd_size);

EV_FUN_DEF(SPI_CMD_WRITE,const ev_obj_t *cs_io,uint32_t cmd,uint8_t cmd_size,uint8_t dummy,const uint8_t *data,uint32_t size);
EV_FUN_DEF(SPI_CMD_READ, const ev_obj_t *cs_io,uint32_t cmd,uint8_t cmd_size,uint8_t dummy,uint8_t *data,uint32_t size);

EV_FUN_DEF(SPI_MEM_WRITE,const ev_obj_t *cs_io,uint32_t cmd,uint8_t cmd_size,uint32_t addr,uint8_t addr_size,uint8_t dummy,const uint8_t *data,uint32_t size);
EV_FUN_DEF(SPI_MEM_READ, const ev_obj_t *cs_io,uint32_t cmd,uint8_t cmd_size,uint32_t addr,uint8_t addr_size,uint8_t dummy,uint8_t *data,uint32_t size);


extern const ev_model_t ev_spi_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    //句柄 内部变量
    void*       handle;

    uint8_t     (*init)(void* handle,ev_spi_mode_e mode,uint32_t max_Mhz);

    uint8_t     (*write)(void* handle,const uint8_t *dat,uint16_t len);

    uint8_t     (*read)(void* handle,uint8_t *dat,uint16_t len);

    void        (*uninit)(void* handle);


}EVO_ATTR_T(ev_spi_m);
#define ev_spi_m_attr_init  .handle = EV_TO_RAM(void*,0),

#endif

