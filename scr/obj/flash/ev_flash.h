#ifndef __EDEV_FLASH_H__
#define __EDEV_FLASH_H__


#include "./core/ev_core.h"


enum{
    EVO_E(FLASH_WRITE) = EVO_E(START),
    EVO_E(FLASH_READ),
    EVO_E(FLASH_ERASE),
    EVO_E(FLASH_INFO),
};


typedef struct {
    uint32_t read_gran;     //读取颗粒
    uint32_t write_gran;    //写入颗粒

    union{                  //块/页 尺寸、擦除颗粒

        uint32_t block_size;    
        uint32_t erase_gran;    
    };

    uint32_t size;//falsh 尺寸
} ev_flash_info_t;

//擦除指定数量块/扇区
EV_FUN_DEF(FLASH_INFO,ev_flash_info_t *info);


EV_FUN_DEF(FLASH_WRITE,uint32_t offset,const uint8_t *data,uint32_t size);

EV_FUN_DEF(FLASH_READ,uint32_t offset,uint8_t *data,uint32_t size);

//擦除指定数量块/扇区
EV_FUN_DEF(FLASH_ERASE,uint32_t offset,uint32_t num);


extern const ev_model_t ev_flash_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    ev_flash_info_t info;

    uint8_t     (*init)(void);

    uint8_t     (*write)(uint32_t offset,const uint8_t *data,uint32_t size);

    uint8_t     (*read)(uint32_t offset,const uint8_t *data,uint32_t size);

    uint8_t     (*erase)(uint32_t offset,uint32_t num);

    uint8_t     (*uninit)(void);

}EVO_ATTR_T(ev_flash_m);
#define ev_flash_m_attr_init  

#endif

