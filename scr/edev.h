#ifndef __EDEV_H__
#define __EDEV_H__

#include "./edev_config.h"
#include "./core/ev_core.h"


//创建设备
extern ev_obj_s* ev_obj_create(ev_type_s *type);

//释放设备
extern void ev_obj_free(ev_obj_s *obj);

//调用设备方法
#define ev_obj_fun(obj, op, ...) _ev_obj_fun(obj, op,&(const EVO_S(EVO_E)){__VA_ARGS__})

#endif
