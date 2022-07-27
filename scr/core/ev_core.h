#ifndef __EDEV_CORE_H__
#define __EDEV_CORE_H__

#include "stdint.h"
#include "./core/ev_pp.h"

typedef struct ev_obj_t ev_obj_t;
typedef struct ev_type_t ev_type_t;

#define EV_TO_RAM(type,...)  (type *)(         type[]){__VA_ARGS__}
#define EV_TO_ROM(type,...)  (type *)(const    type[]){__VA_ARGS__}


//------------------------------
//方法原型
typedef uint8_t (*edev_obj_fun_t)(const ev_obj_t *self,void *arg);


//设备类型
typedef struct ev_type_t{
    char                *name;

    uint16_t        total;      //方法总数
    const edev_obj_fun_t  *list;       //方法清单
}ev_type_t;

//定义list时的快捷方法
#define EV_TYPE_LIST(type)              type##_list
#define EV_TYPE_TOTAL(type)             sizeof(EV_TYPE_LIST(type))/sizeof(edev_obj_fun_t)
#define EV_TYPE_FUN(type,OP)            type##_##OP
//方法定义
#define EV_TYPE_FUN_DEF(type,OP)        static uint8_t EV_TYPE_FUN(type,OP)(const ev_obj_t *self,void *_arg)
//获得参数到 arg变量
#define EV_TYPE_FUN_GET_ARG(type,OP)    const EVO_T(OP) *arg = (EVO_T(OP) *)_arg;const EVO_ATTR_T(type) *attr = (const EVO_ATTR_T(type) *)self->attr;


//方法定义接口
#define _EV_FUN_ARG_DEF(CTX,VAR,IDX)  VAR;
#define EV_FUN_DEF(OP,...) \
typedef struct {\
EV_PP_IF(EV_PP_NOT(EV_PP_IS_EMPTY(__VA_ARGS__)), EV_PP_FOR_EACH(_EV_FUN_ARG_DEF,OP, __VA_ARGS__),uint8_t nul;)\
}EVO_T(OP)




#define EV_TYPE_LIST_ADD_FUN(type,OP)    [EVO_E(OP)] = EV_TYPE_FUN(type,OP)
#define _EV_TYPE_LIST_ADD_FUN(type,OP,N)    EV_TYPE_LIST_ADD_FUN(type,OP),
#define _EV_TYPE_LIST_FILL0(...)   0,0
#define EV_TYPE_LIST_DEF(type,...) static const edev_obj_fun_t EV_TYPE_LIST(type)[] = {\
                EV_PP_IF(EV_PP_NOT(EV_PP_IS_EMPTY(__VA_ARGS__)), EV_PP_FOR_EACH,_EV_TYPE_LIST_FILL0)(_EV_TYPE_LIST_ADD_FUN,type, __VA_ARGS__)}

//为方便调试，不过度封装
#define EV_TYPE_DEF(type) ( ev_type_t ){\
    .name = #type,\
    .total = EV_TYPE_TOTAL(type),\
    .list  = EV_TYPE_LIST(type),\
    };\




//基本属性，放在头位置 成员名base
typedef struct {
    void **lock;
    char nul;
    const char  *name;      //对象名，用于打印信息
}ev_obj_attr_base_t;

//设备对象结构
typedef struct ev_obj_t{
    const ev_type_t             *type;      //方法列表
    const ev_obj_attr_base_t    *attr;      //对象属性
}ev_obj_t;

#define EVO_ATTR_BASE_INIT   .base.nul = 0,
#define EVO_ATTR_INIT(type)  type##_attr_init
#define EVO_ATTR_T(type)     type##_attr_t
  
#define EVO_ATTR_DEF(type, ...)  (const ev_obj_attr_base_t*)(const EVO_ATTR_T(type) []){{EV_PP_NANG_FILL0(__VA_ARGS__)}}

#define _ev_obj_forge(_type, ...)  {.type = &_type,.attr = EVO_ATTR_DEF(_type, EVO_ATTR_BASE_INIT EVO_ATTR_INIT(_type) __VA_ARGS__)}

#define ev_obj_add_lock   .base.lock = EV_TO_RAM(void*,0),






//断言-错误返回1
#define ev_obj_assert(obj) \
if(!obj){ev_warning("%s obj null\r\n",__fun__);return 1;}

#define ev_type_assert(obj) \
if(!obj->type){ev_warning("%s type null\r\n",__fun__);return 1;}

#define ev_attr_assert(obj) \
if(!obj->attr){ev_warning("%s attr null\r\n",__fun__);return 1;}

#define ev_op_assert(obj,op) \
if((op >= obj->type->total)&&(obj->type->list[EVO_E(RELAY)] == 0))\
{ev_warning("%s:%s no fun op:%d\r\n",__fun__,obj->type->name,op);return 1;}



//--------------------------------
//选项edev Options -> evo
#define EVO_E(OP) EVO_##OP##_E
#define EVO_T(OP) EVO_##OP##_ARG_T
extern uint8_t __ev_obj_fun(const ev_obj_t *obj, uint16_t op, void *arg);
#define _ev_obj_fun(obj, op, ...) __ev_obj_fun(obj, EVO_E(op),(void *)&(const EVO_T(op)){EV_PP_NANG_FILL0(__VA_ARGS__)})

//基础选项

//基础选项列表,每一个设备都需要有的选项
enum{
    EVO_E(RELAY) = 0,       //当找不到实现时会调用，可向下继续传递或提示错误
    EVO_E(HELP),            //帮助信息,可重定义
    EVO_E(POWER),           //默认电源配置,可重定义
    EVO_E(SET_CB),          //默认设置回调,可重定义
    EVO_E(INIT),            //配置初始化
    EVO_E(UNINIT),          //反初始化
    EVO_E(STARE),           //设备方法的开始
};//最多支持65535个，没必要考虑更多的情况

//EVO_HELP 帮助信息 注释或打印
EV_FUN_DEF(HELP,uint16_t op);

//--------------------------------
//电源等级edev power -> evp
enum{
    EVP_NONE = 0,    //缺省
    EVP_HIGH,        //最大功耗
    EVP_IDLE,        //空闲，低功耗
    EVP_OPEN,        //正常活跃中
    EVP_CLOSE,       //完全关闭，断电
};
//POWER 默认电源配置,可重定义
//uint8_t    evp;//电源等级
EV_FUN_DEF(POWER,uint8_t evp);


EV_FUN_DEF(RELAY,uint16_t op,void *arg);

//SET_CB 默认的设置回调
typedef void (*ev_obj_cb_t)(void *param,uint16_t event,void *arg);
//ev_obj_cb_t cb;//回调
//void *param;//传给回调
EV_FUN_DEF(SET_CB,ev_obj_cb_t cb,void *param);


//INIT 初始化设备
EV_FUN_DEF(INIT);

//UNINIT 反初始化
EV_FUN_DEF(UNINIT);

//--------------------------------
//事件类型edev event -> eve
#define EVE_T(EVE_E) EVE_E##_ARG_T

enum{
    EVE_STARE = 0,    //设备事件开始
};//最多支持65535-EVE_STARE个，没必要考虑更多的情况



#endif
