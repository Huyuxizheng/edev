#ifndef __EDEV_W25NXX_H__
#define __EDEV_W25NXX_H__



#include "./core/ev_core.h"



typedef struct EVO_ATTR_T(ev_w25nxx_spi_m){//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *spi;
    const ev_obj_t      *cs_io;
    const ev_obj_t      *buff;//2112字节及以上
    //uint8_t             *array;
    //uint32_t            array_size;
}EVO_ATTR_T(ev_w25nxx_ecc_spi_m);
#define ev_w25nxx_ecc_spi_m_attr_init 

extern const ev_model_t ev_w25nxx_ecc_spi_m;



typedef struct{//属性列表
    EVO_ATTR_T(ev_w25nxx_ecc_spi_m);
}EVO_ATTR_T(ev_w25n01_spi_m);
#define ev_w25n01_spi_m_attr_init  ev_w25nxx_ecc_spi_m_attr_init

extern const ev_model_t ev_w25n01_spi_m;




#endif