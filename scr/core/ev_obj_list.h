#ifndef __EDEV_OBJ_LIST_H__
#define __EDEV_OBJ_LIST_H__
#include "./core/ev_core.h"

typedef struct ev_obj_node_t ev_obj_node_t;

typedef struct ev_obj_node_t{
    ev_obj_node_t  *next;
    ev_obj_t       *obj;//ev_obj_list_s
}ev_obj_node_t;

typedef struct ev_obj_list_t{
    ev_obj_node_t  *next;
}ev_obj_list_t;

//检查OBJ是否否在列表
extern uint8_t ev_obj_list_check_obj(ev_obj_list_t *list,ev_obj_t    *obj);
//增加OBJ到列表
extern uint8_t ev_obj_list_add_obj(ev_obj_list_t *list,ev_obj_t    *obj);
//增加OBJ到列表，过滤重复
extern uint8_t ev_obj_list_add_obj_filter(ev_obj_list_t *list,ev_obj_t    *obj);
//删除OBJ
extern uint8_t ev_obj_list_del_obj(ev_obj_list_t *list,ev_obj_t    *obj);
//复位列表
extern void    ev_obj_list_reset(ev_obj_list_t *list);



#endif
