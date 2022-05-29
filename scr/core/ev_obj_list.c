#include "./core/ev_obj_list.h"
#include "edev_config.h"

uint8_t ev_obj_list_add_obj_filter(ev_obj_list_t *list,ev_obj_t    *obj)
{
    ev_obj_node_t *node = (ev_obj_node_t *)list;
    while(node->next)
    {
        if(node->next->obj == obj)
        {
            return 1;
        }
        node = node->next;
    }
    node->next = ev_malloc(sizeof(ev_obj_node_t));
    if(!node->next)
    {
        return 1;
    }
    node->next->obj = obj;
    node->next->next = 0;
    
    return 0;
}

uint8_t ev_obj_list_add_obj(ev_obj_list_t *list,ev_obj_t    *obj)
{
    ev_obj_node_t *node = (ev_obj_node_t *)list;
    while(node->next)
    {
        node = node->next;
    }
    node->next = ev_malloc(sizeof(ev_obj_node_t));
    if(!node->next)
    {
        return 1;
    }
    node->next->obj = obj;
    node->next->next = 0;
    
    return 0;
}

uint8_t ev_obj_list_del_obj(ev_obj_list_t *list,ev_obj_t    *obj)
{
    ev_obj_node_t *node = (ev_obj_node_t *)list;
    ev_obj_node_t *temp = 0;
    while((node->next != 0) && (node->next->obj != obj))
    {
        node = node->next;
    }
    if(!node->next)
    {
        return 1;
    }
    temp = node->next->next;
    ev_free(node->next);
    node->next = temp;
    
    return 0;
}
void ev_obj_list_del_all_node(ev_obj_node_t *node)
{
    if(node->next)
    {
        ev_obj_list_del_all_node(node->next);
        node->next = 0;
    }
    ev_free(node);
    return ;
}
void ev_obj_list_reset(ev_obj_list_t *list)
{
    if(list->next)
    {
        ev_obj_list_del_all_node(list->next);
    }
    
    return;
}

uint8_t ev_obj_list_check_obj(ev_obj_list_t *list,ev_obj_t    *obj)
{
    ev_obj_node_t *node = (ev_obj_node_t *)list;
    while((node->next != 0) && (node->next->obj != obj))
    {
        node = node->next;
    }
    if(!node->next)
    {
        return 0;
    }
    return 1;
}


