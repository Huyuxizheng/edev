#ifndef __EDEV_ADP_H__
#define __EDEV_ADP_H__

/*
一般的LED操作，可设置点亮，或反转电平
*/


#include "./core/ev_core.h"


extern const ev_model_t ev_adp_m;


#define _EV_ADP_ADD_LIST(CTX,VAR,IDX)  VAR,
#define _EV_ADP_ADD_LIST_0(...)  0

#define ev_adp_add_list(...) \
    .list = (const ev_obj_t * const []){ EV_PP_IF(EV_PP_NOT(EV_PP_IS_EMPTY(__VA_ARGS__)),EV_PP_FOR_EACH ,_EV_ADP_ADD_LIST_0)(_EV_ADP_ADD_LIST,0,__VA_ARGS__) },\
    .list_len = EV_PP_NARG(__VA_ARGS__) ,

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      **obj;
    const ev_obj_t      **list;
    uint8_t             list_len;
}EVO_ATTR_T(ev_adp_m);

#define ev_adp_m_attr_init .obj = EV_TO_RAM(const ev_obj_t *,0),

#endif
