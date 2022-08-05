#ifndef __EDEV_H__
#define __EDEV_H__

#include "./edev_config.h"
#include "./core/ev_core.h"

#include "./obj/led/ev_led.h"
#include "./obj/tp/ev_tp.h"
#include "./obj/drive/ev_gpio.h"

//锻造版驱动
#define ev_drive_forge(DRI, ...)    _ev_drive_forge(DRI, __VA_ARGS__)
#define ev_obj_forge(type, ...)    _ev_obj_forge(type, __VA_ARGS__)


//调用设备方法
#define ev_obj_fun(obj, op, ...)  _ev_obj_fun(&obj, op,__VA_ARGS__)

//调用多次
#define ev_obj_funs(obj, op, ...)       _ev_obj_funs(&obj, op, __VA_ARGS__) 
#define ev_objs_fun(obj_list,op,...)    __ev_objs_fun(_EV_OBJS_FUN_TO_CALL_USER,obj_list,op,__VA_ARGS__) 
#define ev_objs_funs(obj_list,op,arg_list)    __ev_objs_funs(_EV_OBJS_FUNS_TO_CALL_USER,obj_list,op,arg_list)
#define ev_objs_funs_syn(obj_list,op,arg_list)    __ev_objs_funs_syn(__EV_OBJS_FUNS_SYN_TO_CALL_USER,obj_list,op,arg_list) 

#endif
