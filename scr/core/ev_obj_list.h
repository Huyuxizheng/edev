#ifndef __EDEV_OBJ_LIST_H__
#define __EDEV_OBJ_LIST_H__
#include "./core/ev_core.h"

typedef struct ev_obj_node_s ev_obj_node_s;

typedef struct ev_obj_node_s{
    ev_obj_node_s  *next;
    ev_obj_s       *obj;//ev_obj_list_s Œ¥ π”√
}ev_obj_node_s;

typedef struct ev_obj_list_s{
    ev_obj_node_s  *next;
}ev_obj_list_s;

extern uint8_t ev_obj_list_add_obj(ev_obj_list_s *list,ev_obj_s    *obj);
extern uint8_t ev_obj_list_del_obj(ev_obj_list_s *list,ev_obj_s    *obj);
extern void    ev_obj_list_reset(ev_obj_list_s *list);

#endif
