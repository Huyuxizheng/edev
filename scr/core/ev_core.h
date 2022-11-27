#ifndef __EDEV_CORE_H__
#define __EDEV_CORE_H__

#include "stdint.h"
#include "./core/ev_pp.h"

typedef struct ev_obj_t ev_obj_t;
typedef struct ev_model_t ev_model_t;

#define EV_TO_RAM(type,...)  (type *)(type []){__VA_ARGS__}
#define EV_TO_ROM(type,...)  (type *)(type const[]){__VA_ARGS__}


//------------------------------
//方法原型
typedef uint8_t (*edev_obj_fun_t)(const ev_obj_t *self,void *arg);


//设备类型
typedef struct ev_model_t{
    char                    *name;

    uint16_t                total;      //方法总数
    const edev_obj_fun_t    *list;       //方法清单

    const struct ev_model_t *parent;
}ev_model_t;

//定义list时的快捷方法
#define EV_MODEL_LIST(model)              model##_list
#define EV_MODEL_TOTAL(model)             sizeof(EV_MODEL_LIST(model))/sizeof(edev_obj_fun_t)
#define EV_MODEL_FUN(model,OP)            model##_##OP
//方法定义
#define EV_MODEL_FUN_DEF(model,OP)        static uint8_t EV_MODEL_FUN(model,OP)(const ev_obj_t *self,void *_arg)
//获得参数到 arg变量
#define EV_MODEL_FUN_GET_ARG(model,OP)    const EVO_T(OP) *arg = (EVO_T(OP) *)_arg;const EVO_ATTR_T(model) *attr = (const EVO_ATTR_T(model) *)self->attr;


//方法定义接口
#define _EV_FUN_ARG_DEF(CTX,VAR,IDX)  VAR;
#define EV_FUN_DEF(OP,...) \
typedef struct {\
EV_PP_IF(EV_PP_NOT(EV_PP_IS_EMPTY(__VA_ARGS__)), EV_PP_FOR_EACH(_EV_FUN_ARG_DEF,OP, __VA_ARGS__),uint8_t nul;)\
}EVO_T(OP)


#define EV_MODEL_LIST_ADD_FUN(model,OP)    [EVO_E(OP)] = EV_MODEL_FUN(model,OP)
#define _EV_MODEL_LIST_ADD_FUN(model,OP,N)    EV_MODEL_LIST_ADD_FUN(model,OP),
#define _EV_MODEL_LIST_FILL0(...)   0,0
#define EV_MODEL_LIST_DEF(model,...) static edev_obj_fun_t const EV_MODEL_LIST(model)[] = {\
                EV_PP_IF(EV_PP_NOT(EV_PP_IS_EMPTY(__VA_ARGS__)), EV_PP_FOR_EACH,_EV_MODEL_LIST_FILL0)(_EV_MODEL_LIST_ADD_FUN,model, __VA_ARGS__)}

#define EV_MODEL_DEF(model , ...) ( ev_model_t ){\
    .name = #model,\
    .total = EV_MODEL_TOTAL(model),\
    .list  = EV_MODEL_LIST(model),\
    .parent = EV_PP_IF(EV_PP_NARG(__VA_ARGS__),(& EV_PP_GET_N_0(__VA_ARGS__)),0),\
    };\


//基本属性，放在头位置 成员名base
typedef struct {
    void **lock;
    char nul;
    const char  *name;      //对象名，用于打印信息
}ev_obj_attr_base_t;

//设备对象结构
typedef struct ev_obj_t{
    const ev_model_t             *model;      //方法列表
    const ev_obj_attr_base_t    *attr;      //对象属性
}ev_obj_t;

#define EVO_ATTR_BASE_INIT   .base.nul = 0,
#define EVO_ATTR_INIT(model)  model##_attr_init
#define EVO_ATTR_T(model)     model##_attr_t
  
#define EVO_ATTR_DEF(model, ...)  (const ev_obj_attr_base_t*)(const EVO_ATTR_T(model) []){{EV_PP_NANG_FILL0(__VA_ARGS__)}}

#define _ev_obj_forge(_model, ...)  {.model = &_model,.attr = EVO_ATTR_DEF(_model, EVO_ATTR_BASE_INIT EVO_ATTR_INIT(_model) __VA_ARGS__)}

#define ev_obj_add_lock             .base.lock = EV_TO_RAM(void*,0),


//断言-错误返回1
#define ev_obj_assert(obj) \
if(!obj){ev_warning("%s obj null\r\n",__fun__);return 1;}

#define ev_model_assert(obj) \
if(!obj->model){ev_warning("%s model null\r\n",__fun__);return 1;}

#define ev_attr_assert(obj) \
if(!obj->attr){ev_warning("%s attr null\r\n",__fun__);return 1;}

#define ev_op_assert(obj,op) \
if((op >= obj->model->total)&&(obj->model->list[EVO_E(RELAY)] == 0))\
{ev_warning("%s:%s no fun op:%d\r\n",__fun__,obj->model->name,op);return 1;}


//--------------------------------
//选项定义宏方法edev Options -> evo
extern uint8_t __ev_obj_fun(const ev_obj_t *obj, uint16_t op, void *arg);

#define EVO_E(OP) EVO_##OP##_E
#define EVO_T(OP) EVO_##OP##_ARG_T
#define _ev_obj_fun(obj, op, ...)           __ev_obj_fun(obj, EVO_E(op),(void *)&(const EVO_T(op)){EV_PP_NANG_FILL0(__VA_ARGS__)})

#define _EV_OBJ_FUN_TO_CALL(...)            _ev_obj_fun(__VA_ARGS__)
#define _EV_OBJ_FUNS_TO_CALL(CTX,VAR,IDX)   EV_PP_IF(IDX,;,) _EV_OBJ_FUN_TO_CALL(EV_PP_REMOVE_PARENS(CTX) , EV_PP_REMOVE_PARENS(VAR))
#define _EV_OBJ_FUNS_TO_CALL_0(...)    

#define _EV_OBJ_FUNS_I(op,...)              EV_PP_IF(EV_PP_NOT(EV_PP_IS_EMPTY(__VA_ARGS__)), EV_PP_FOR_EACH,_EV_OBJ_FUNS_TO_CALL_0)(_EV_OBJ_FUNS_TO_CALL,op, __VA_ARGS__)
#define __ev_obj_funs(obj, op, ...)         _EV_OBJ_FUNS_I((obj,op),__VA_ARGS__)
#define _ev_obj_funs(obj, op, ...)          __ev_obj_funs(obj, op, __VA_ARGS__)

#define _EV_OBJS_FUN_TO_CALL(CTX,VAR,IDX)               EV_PP_IF(IDX,;,) _EV_OBJ_FUN_TO_CALL(VAR,EV_PP_REMOVE_PARENS(CTX))
#define _EV_OBJS_FUN_TO_CALL_USER(CTX,VAR,IDX)          EV_PP_IF(IDX,;,) _EV_OBJ_FUN_TO_CALL(&##VAR,EV_PP_REMOVE_PARENS(CTX))

#define _EV_OBJS_FUN_I(...)                             EV_PP_FOR_EACH_N(__VA_ARGS__)

#define __EV_OBJS_FUN(call,...)                         _EV_OBJS_FUN_I( EV_PP_DEC(EV_PP_DEC(EV_PP_NARG(__VA_ARGS__))), call,\
EV_PP_IF( EV_PP_NOT(EV_PP_IS_EMPTY(EV_PP_REMOVE_PARENS(EV_PP_GET_N(EV_PP_DEC(EV_PP_NARG(__VA_ARGS__)),__VA_ARGS__)))) ,\
(EV_PP_GET_N(EV_PP_DEC(EV_PP_DEC(EV_PP_NARG(__VA_ARGS__))),__VA_ARGS__),EV_PP_REMOVE_PARENS(EV_PP_GET_N(EV_PP_DEC(EV_PP_NARG(__VA_ARGS__)),__VA_ARGS__))),\
(EV_PP_GET_N(EV_PP_DEC(EV_PP_DEC(EV_PP_NARG(__VA_ARGS__))),__VA_ARGS__))\
),__VA_ARGS__)

#define __ev_objs_fun(call,...)                         EV_PP_IF( EV_PP_BOOL(EV_PP_DEC(EV_PP_DEC(EV_PP_NARG(__VA_ARGS__)))),__EV_OBJS_FUN(call,__VA_ARGS__),)
#define _ev_objs_fun(obj_list,op,...)                   __ev_objs_fun(_EV_OBJS_FUN_TO_CALL,obj_list,op,__VA_ARGS__) 

#define __EV_OBJS_FUNS_TO_CALL(...)                     _ev_obj_funs(__VA_ARGS__)
#define _EV_OBJS_FUNS_TO_CALL(CTX,VAR,IDX)              EV_PP_IF(IDX,;,)  __EV_OBJS_FUNS_TO_CALL(VAR,EV_PP_REMOVE_PARENS(CTX))

#define __EV_OBJS_FUNS_TO_CALL_USER(...)                ev_obj_funs(__VA_ARGS__)
#define _EV_OBJS_FUNS_TO_CALL_USER(CTX,VAR,IDX)         EV_PP_IF(IDX,;,) __EV_OBJS_FUNS_TO_CALL_USER(VAR,EV_PP_REMOVE_PARENS(CTX))
#define __ev_objs_funs(call,obj_list,op,arg_list)       EV_PP_FOR_EACH_S1_N(EV_PP_NARG(EV_PP_REMOVE_PARENS(obj_list)),call,(op,EV_PP_REMOVE_PARENS(arg_list)),EV_PP_REMOVE_PARENS(obj_list))

#define _ev_objs_funs(obj_list,op,arg_list)             __ev_objs_funs(_EV_OBJS_FUNS_TO_CALL,obj_list,op,arg_list) 

#define __EV_OBJS_FUNS_SYN_TO_CALL(...)                 _ev_objs_fun(__VA_ARGS__)
#define _EV_OBJS_FUNS_SYN_TO_CALL(CTX,VAR,IDX)          EV_PP_IF(IDX,;,)  __EV_OBJS_FUNS_SYN_TO_CALL(EV_PP_REMOVE_PARENS(CTX),VAR)

#define __EV_OBJS_FUNS_SYN_TO_CALL_USER(...)            ev_objs_fun(__VA_ARGS__)
#define _EV_OBJS_FUNS_SYN_TO_CALL_USER(CTX,VAR,IDX)     EV_PP_IF(IDX,;,) __EV_OBJS_FUNS_SYN_TO_CALL_USER(EV_PP_REMOVE_PARENS(CTX),VAR)
#define __ev_objs_funs_syn(call,obj_list,op,arg_list)   EV_PP_FOR_EACH_S1_N(EV_PP_NARG(EV_PP_REMOVE_PARENS(arg_list)),call,(EV_PP_REMOVE_PARENS(obj_list),op),EV_PP_REMOVE_PARENS(arg_list))

#define _ev_objs_funs_syn(obj_list,op,arg_list)         __ev_objs_funs_syn(_EV_OBJS_FUNS_SYN_TO_CALL,obj_list,op,arg_list) 


//调用设备方法
#define ev_obj_fun(obj, op, ...)                    _ev_obj_fun(&obj, op,__VA_ARGS__)
#define ev_obj_funs(obj, op, ...)                   _ev_obj_funs(&obj, op, __VA_ARGS__) 
#define ev_objs_fun(obj_list,op,...)                __ev_objs_fun(_EV_OBJS_FUN_TO_CALL_USER,obj_list,op,__VA_ARGS__) 
#define ev_objs_funs(obj_list,op,arg_list)          __ev_objs_funs(_EV_OBJS_FUNS_TO_CALL_USER,obj_list,op,arg_list)
#define ev_objs_funs_syn(obj_list,op,arg_list)      __ev_objs_funs_syn(__EV_OBJS_FUNS_SYN_TO_CALL_USER,obj_list,op,arg_list) 

//内部库调用
#define __ev_do(obj, op, arg)         __ev_obj_fun(obj, op, arg)
#define _ev_do(obj, op, ...)         _ev_obj_fun(obj, op,__VA_ARGS__)
#define _ev_do_n(obj, op, ...)       _ev_obj_funs(obj, op,__VA_ARGS__)
#define _ev_n_do(obj, op, ...)       _ev_objs_fun(obj, op,__VA_ARGS__)
#define _ev_n_do_n(obj, op, ...)     _ev_objs_funs(obj, op,__VA_ARGS__)
#define _ev_n_do_n_s(obj, op, ...)   _ev_objs_funs_syn(obj, op,__VA_ARGS__)


//基础选项

//基础选项列表,每一个设备都需要有的选项
enum{
    EVO_E(RELAY) = 0,       //当找不到实现时会调用，可向下继续传递或提示错误
    EVO_E(HELP),            //帮助信息,可重定义
    EVO_E(CHECK_OP),        //查询功能是否可用
    EVO_E(POWER),           //默认电源配置,可重定义
    EVO_E(SET_CB),          //默认设置回调,可重定义
    EVO_E(INIT),            //配置初始化
    EVO_E(WRITE),           //写数据
    EVO_E(READ),            //读数据
    EVO_E(UNINIT),          //反初始化
    EVO_E(START),           //设备方法的开始
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

//可用返回1
EV_FUN_DEF(CHECK_OP,uint16_t op);

//INIT 初始化设备
EV_FUN_DEF(INIT);


EV_FUN_DEF(WRITE,uint8_t *data,uint32_t size);

EV_FUN_DEF(READ,uint8_t *data,uint32_t size);

//UNINIT 反初始化
EV_FUN_DEF(UNINIT);

//--------------------------------
//事件类型edev event -> eve
#define EVE_T(EVE_E) EVE_E##_ARG_T

enum{
    EVE_STARE = 0,    //设备事件开始
};//最多支持65535-EVE_STARE个，没必要考虑更多的情况



#endif
