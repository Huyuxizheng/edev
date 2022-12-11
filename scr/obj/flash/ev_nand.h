#ifndef __EDEV_NAND_H__
#define __EDEV_NAND_H__


#include "./core/ev_core.h"


enum{
    EVO_E(NAND_WRITE) = EVO_E(START),//写受ECC保护的数据和OOB
    EVO_E(NAND_READ),//读取受ECC保护的数据和OOB
    EVO_E(NAND_ERASE),//擦除
    EVO_E(NAND_INFO),
    EVO_E(NAND_NOOB_WRITE),//可以单独写的OOB，不参与校验ECC
    EVO_E(NAND_NOOB_READ),//不受ECC影响的OOB读取
    EVO_E(NAND_CHECK_BAD_BLOCK),//检测坏块
    EVO_E(NAND_SET_BAD_BLOCK),//设置坏块
};


typedef struct {
    uint32_t page_gran;     //页大小
    uint32_t block_size;    //块大小
    uint32_t oob_size;      //可用oob大小
    uint32_t block_num;     //块数量
    uint32_t noob_size;     //不被ECC保护的oob大小(不带ECC的全部在这里)
} ev_nand_info_t;

EV_FUN_DEF(NAND_INFO,ev_nand_info_t *info);


EV_FUN_DEF(NAND_WRITE,uint32_t page_offset,const uint8_t *data,uint32_t size,const uint8_t *oob_data,uint32_t oob_size);

EV_FUN_DEF(NAND_READ,uint32_t page_offset,uint8_t *data,uint32_t size,uint8_t *oob_data,uint32_t oob_size);

//擦除指定块
EV_FUN_DEF(NAND_ERASE,uint32_t page_offset);

//设置坏块
EV_FUN_DEF(NAND_CHECK_BAD_BLOCK,uint32_t page_offset);
EV_FUN_DEF(NAND_SET_BAD_BLOCK,uint32_t page_offset);


//不受ECC保护的 OOB读写
EV_FUN_DEF(NAND_NOOB_WRITE,uint32_t page_offset,const uint8_t *oob_data,uint32_t oob_size);

EV_FUN_DEF(NAND_NOOB_READ,uint32_t page_offset,uint8_t *oob_data,uint32_t oob_size);


#endif

