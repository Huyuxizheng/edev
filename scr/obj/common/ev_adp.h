#ifndef __EDEV_ADP_H__
#define __EDEV_ADP_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"


extern const ev_type_t ev_adp_type;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    ev_obj_t            **obj;
    ev_obj_t            **list;
    uint8_t             list_len;
}EVO_ATTR_T(ev_adp_type);
#define ev_adp_type_attr_init 

#endif
