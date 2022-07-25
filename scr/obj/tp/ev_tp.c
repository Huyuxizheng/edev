// #include "./dev/tp/ev_tp.h"
// #include "edev_config.h"
// #include "./core/ev_obj_list.h"

// typedef struct{
//     ev_obj_attr_base_t base;
//     ev_obj_t        **obj;
//     ev_obj_list_t   *obj_list;
// }ev_tp_attr_t;

// EV_TYPE_FUN_DEF(ev_tp_type,HELP)
// {
//     EV_TYPE_FUN_GET_ARG(HELP);
// /*
                                   
// */

//     return 0;
// }


// EV_TYPE_FUN_DEF(ev_tp_type,LINK)
// {
//     EV_TYPE_FUN_GET_ARG(LINK);
//     if(!arg->obj){return 1;}
//     ev_tp_attr_t *attr = self->attr;

//     if(_ev_obj_fun(arg->obj,SUPPORT,self) == 0)
//     {//如果对象支持
//         if(ev_obj_list_add_obj_filter(&(attr->obj_list),arg->obj) == 0)
//         {//如果注册成功增加持股
//             _ev_obj_share_add(arg->obj,self);
//         }
            
//     }

//     return 1;
// }

// EV_TYPE_FUN_DEF(ev_tp_type,POWER)
// {
//     EV_TYPE_FUN_GET_ARG(POWER);

//     ev_tp_attr_t *attr = self->attr;

//     if(!attr->obj){return 1;}//未自适应

//     switch(arg->evp)
//     {
//         case EVP_NONE:case EVP_HIGH:case EVP_OPEN:
//         _ev_obj_fun(attr->obj,POWER,arg->evp);
//         _ev_obj_fun(attr->obj,INIT,0);
//         break;
//         case EVP_IDLE:case EVP_CLOSE:
//         _ev_obj_fun(attr->obj,POWER,arg->evp);
//         break;
//     }  
//     return 0;
// }

// EV_TYPE_FUN_DEF(ev_tp_type,ADAPT)
// {
//     EV_TYPE_FUN_GET_ARG(ADAPT);

//     ev_tp_attr_t *attr = self->attr;

//     while(attr->obj_list.next)
//     {
//         ev_obj_t      *ic_obj = attr->obj_list.next->obj;

//         _ev_obj_fun(ic_obj,POWER,EVP_OPEN);
//         if(_ev_obj_fun(ic_obj,ADAPT,1) == 0)
//         {
//             _ev_obj_fun(ic_obj,POWER,EVP_CLOSE);
//             while(attr->obj_list.next->next)
//             {
//                  ev_obj_t      *free_obj = attr->obj_list.next->next->obj;
//                 ev_obj_list_del_obj(&attr->obj_list,free_obj);
//                 if(arg->clean_flag)
//                 {
//                     ev_obj_free(free_obj);
//                 }
//             }
//             attr->obj = ic_obj;
//             return 0;
//         }
//         else
//         {
//             _ev_obj_fun(ic_obj,POWER,EVP_CLOSE);

//             ev_obj_list_del_obj(&attr->obj_list,ic_obj);
//             if(arg->clean_flag)
//             {
//                 ev_obj_free(ic_obj);
//             }
//         }
        
//     }
//     return 1;
// }

// EV_TYPE_FUN_DEF(ev_tp_type,TP_GET)
// {
//     EV_TYPE_FUN_GET_ARG(TP_GET);

//     ev_tp_attr_t *attr = self->attr;

//     if(!attr->obj){return 1;}//未自适应

//     _ev_obj_fun(attr->obj,TP_IC_GET,arg->out);

//     return 0;
// }




// static const edev_obj_fun_t EV_TYPE_LIST(ev_tp_type)[] ={
//     EV_TYPE_LIST_ADD_FUN(ev_tp_type,HELP),
//     EV_TYPE_LIST_ADD_FUN(ev_tp_type,LINK),
//     EV_TYPE_LIST_ADD_FUN(ev_tp_type,POWER),
//     EV_TYPE_LIST_ADD_FUN(ev_tp_type,ADAPT),
//     EV_TYPE_LIST_ADD_FUN(ev_tp_type,TP_GET),
// };

// const ev_type_t ev_tp_type = {
//     .name = "ev_tp_type",

//     .total = EV_TYPE_TOTAL(ev_tp_type),
//     .list  = EV_TYPE_LIST(ev_tp_type),
// };






