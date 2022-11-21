#ifndef __EDEV_H__
#define __EDEV_H__

#include "./edev_config.h"
#include "./core/ev_core.h"

#include "./obj/common/ev_adp.h"
#include "./obj/common/ev_heap.h"

#include "./obj/led/ev_led.h"

#include "./obj/tp/ev_tp.h"
#include "./obj/tp/gt9147/ev_tp_gt9147.h"

#include "./obj/hall_ang/ev_hall_ang.h"
#include "./obj/hall_ang/as5600/ev_as5600.h"


#include "./obj/drive/ev_gpio.h"
#include "./obj/drive/ev_i2c_imit.h"

//锻造版驱动
#define ev_obj_forge(model, ...)        _ev_obj_forge(model, __VA_ARGS__)
#define ev_obj_forge_p(model, ...)      EV_TO_ROM( ev_obj_t, _ev_obj_forge(model, __VA_ARGS__))
#define ev_obj_forge_rom(model, ...)    EV_TO_ROM( ev_obj_t, _ev_obj_forge(model, __VA_ARGS__))
#define ev_obj_forge_ram(model, ...)    EV_TO_RAM( ev_obj_t, _ev_obj_forge(model, __VA_ARGS__))

#define ev_forge(model, ...)            _ev_obj_forge(model, __VA_ARGS__)
#define ev_forge_p(model, ...)          EV_TO_ROM( ev_obj_t, _ev_obj_forge(model, __VA_ARGS__))
#define ev_forge_rom(model, ...)        EV_TO_ROM( ev_obj_t, _ev_obj_forge(model, __VA_ARGS__))
#define ev_forge_ram(model, ...)        EV_TO_RAM( ev_obj_t, _ev_obj_forge(model, __VA_ARGS__))

#define ev_do(obj, op, ...)             ev_obj_fun(obj, op,__VA_ARGS__)
#define ev_do_n(obj, op, ...)           ev_obj_funs(obj, op,__VA_ARGS__)
#define ev_n_do(obj, op, ...)           ev_objs_fun(obj, op,__VA_ARGS__)
#define ev_n_do_n(obj, op, ...)         ev_objs_funs(obj, op,__VA_ARGS__)
#define ev_n_do_n_s(obj, op, ...)       ev_objs_funs_syn(obj, op,__VA_ARGS__)



#endif
