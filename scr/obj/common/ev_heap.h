#ifndef __EDEV_HEAP_H__
#define __EDEV_HEAP_H__

#include "./core/ev_core.h"



enum{//方法列表
    EVO_E(MALLOC) = EVO_E(START),
    EVO_E(FREE),
    EVO_E(HEAP_PRINT),
};

EV_FUN_DEF(MALLOC,void **p,uint32_t size);

EV_FUN_DEF(FREE,void *p);

EV_FUN_DEF(HEAP_PRINT);



//方案1
extern const ev_model_t ev_heap1_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    uint8_t             *mem_p;//内存指针
    uint32_t            mem_len;//内存长度

    uint8_t*            *fast_p;//用于快速搜引

}EVO_ATTR_T(ev_heap1_m);

#define ev_heap1_m_attr_init  .fast_p = EV_TO_RAM(uint8_t *,0)




#endif