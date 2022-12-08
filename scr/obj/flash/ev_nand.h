#ifndef __EDEV_NAND_H__
#define __EDEV_NAND_H__


#include "./core/ev_core.h"


enum{
    EVO_E(NAND_WRITE) = EVO_E(START),
    EVO_E(NAND_READ),
    EVO_E(NAND_ERASE),
    EVO_E(NAND_INFO),
    EVO_E(NAND_SET_BAD_BLOCK),
};


typedef struct {
    uint32_t page_gran;     //页大小
    uint32_t block_size;    //块大小
    uint32_t oob_size;      //可用oob大小
    uint32_t block_num;     //块数量
} ev_nand_info_t;

EV_FUN_DEF(NAND_INFO,ev_nand_info_t *info);


EV_FUN_DEF(NAND_WRITE,uint32_t page_offset,const uint8_t *data,uint32_t size,const uint8_t *oob_data,uint32_t oob_size);

EV_FUN_DEF(NAND_READ,uint32_t page_offset,uint8_t *data,uint32_t size,uint8_t *oob_data,uint32_t oob_size);

//擦除指定块
EV_FUN_DEF(NAND_ERASE,uint32_t page_offset);

//设置坏块
EV_FUN_DEF(NAND_SET_BAD_BLOCK,uint32_t page_offset);



enum{
    EVO_E(NAND_ECC_WRITE) = EVO_E(START),
    EVO_E(NAND_ECC_READ),
    EVO_E(NAND_ECC_ERASE),
    EVO_E(NAND_ECC_INFO),
    EVO_E(NAND_ECC_OOB_READ),
    EVO_E(NAND_ECC_OOB_WRITE),
};


typedef struct {
    uint32_t page_gran;     //页大小
    uint32_t block_size;    //块大小
    uint32_t ecc_oob_size;  //可用被ECC保护的oob大小
    uint32_t oob_size;      //可用oob大小
    uint32_t block_num;     //块数量
} ev_nand_info_t;

EV_FUN_DEF(NAND_INFO,ev_nand_info_t *info);


EV_FUN_DEF(NAND_ECC_WRITE,uint32_t page_offset,const uint8_t *data,uint32_t size,const uint8_t *oob_data,uint32_t oob_size);

EV_FUN_DEF(NAND_ECC_READ,uint32_t page_offset,uint8_t *data,uint32_t size,uint8_t *oob_data,uint32_t oob_size);

//擦除指定数量块/扇区
EV_FUN_DEF(NAND_ECC_ERASE,uint32_t block_num,uint32_t num);

EV_FUN_DEF(NAND_ECC_OOB_WRITE,uint32_t page_offset,const uint8_t *oob_data,uint32_t oob_size);

EV_FUN_DEF(NAND_ECC_OOB_READ,uint32_t page_offset,uint8_t *oob_data,uint32_t oob_size);

#endif

