#ifndef __EDEV_CORE_H__
#define __EDEV_CORE_H__

#include "stdint.h"
#include "./dri/ev_dri.h"
#include "./core/ev_pp.h"

typedef struct ev_obj_t ev_obj_t;
typedef struct ev_type_t ev_type_t;

#define EV_TO_RAM(type,...)  (         type[]){__VA_ARGS__}
#define EV_TO_ROM(type,...)  (const    type[]){__VA_ARGS__}


//------------------------------
//方法原型
typedef uint8_t (*edev_obj_fun_t)(ev_obj_t *self,void *arg);


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
#define EV_TYPE_FUN_DEF(type,OP)        static uint8_t EV_TYPE_FUN(type,OP)(ev_obj_t *self,void *_arg)
//获得参数到 arg变量
#define EV_TYPE_FUN_GET_ARG(type,OP)    const EVO_T(OP) *arg = _arg;const EVO_ATTR_T(type) *attr = (const EVO_ATTR_T(type) *)self->attr;

#define EV_TYPE_LIST_ADD_FUN(type,OP)    [EVO_E(OP)] = EV_TYPE_FUN(type,OP)

#define _EV_TYPE_LIST_ADD_FUN(type,OP,N)    EV_TYPE_LIST_ADD_FUN(type,OP) ,

#define EV_TYPE_LIST_DEF(type,...) static const edev_obj_fun_t EV_TYPE_LIST(type)[] = {EV_PP_FOR_EACH(_EV_TYPE_LIST_ADD_FUN,type, __VA_ARGS__)}


//基本属性，放在头位置 成员名base
typedef struct {
    void **lock;
    const char  *name;      //对象名，用于打印信息
}ev_obj_attr_base_t;

//设备对象结构
typedef struct ev_obj_t{
    const ev_type_t             *type;      //方法列表
    const ev_obj_attr_base_t    *attr;      //对象属性
}ev_obj_t;

#define EVO_ATTR_BASE_INIT   .base.lock = EV_TO_RAM(void*,0),
#define EVO_ATTR_INIT(type)  type##_attr_init
#define EVO_ATTR_T(type)     type##_attr_t
  
#define EVO_ATTR_DEF(type, ...)  (const ev_obj_attr_base_t*)(const EVO_ATTR_T(type) []){{EVO_ATTR_BASE_INIT EVO_ATTR_INIT(type) __VA_ARGS__}}

#define _ev_obj_forge(_type, ...)  (ev_obj_t *)(const ev_obj_t []){{.type = &_type,.attr = EVO_ATTR_DEF(_type, __VA_ARGS__)}}




//断言-错误返回1
#define ev_obj_assert(obj) \
if(!obj){ev_warning("%s obj null\r\n",__fun__);return 1;}

#define ev_type_assert(obj) \
if(!obj->type){ev_warning("%s type null\r\n",__fun__);return 1;}

#define ev_attr_assert(obj) \
if(!obj->attr){ev_warning("%s attr null\r\n",__fun__);return 1;}

#define ev_op_assert(obj,op) \
if(op >= obj->type->total)\
{ev_warning("%s:%s no fun op:%d\r\n",__fun__,obj->type->name,op);return 1;}



//--------------------------------
//选项edev Options -> evo
#define EVO_E(OP) EVO_##OP##_E
#define EVO_T(OP) EVO_##OP##_ARG_T
extern uint8_t __ev_obj_fun(ev_obj_t *obj, uint16_t op, void *arg);
#define _ev_obj_fun(obj, op, ...) __ev_obj_fun(obj, EVO_E(op),(void *)&(const EVO_T(op)){__VA_ARGS__})

//基础选项

//基础选项列表,每一个设备都需要有的选项
enum{
    EVO_E(HELP) = 0,        //帮助信息,可重定义
    EVO_E(POWER),           //默认电源配置,可重定义
    EVO_E(LINK),            //默认连接下级设备,可重定义 需要维护下级obj的share属性
    EVO_E(SET_CB),          //默认设置回调,可重定义
    EVO_E(ADAPT),           //开始自适应
    EVO_E(SUPPORT),         //检测是否支持设备
    EVO_E(STARE),           //设备方法的开始
    EVO_E(INIT),            //配置初始化
};//最多支持65535个，没必要考虑更多的情况

//EVO_HELP 帮助信息 注释或打印
typedef struct {
    uint16_t op;
}EVO_T(HELP);

//--------------------------------
//电源等级edev power -> evp
enum{
    EVP_NONE = 0,    //缺省
    EVP_HIGH,        //最大功耗
    EVP_IDLE,        //空闲，低功耗
    EVP_OPEN,        //正常活跃中
    EVP_CLOSE,       //完全关闭，断电
};
//EVO_LINK 默认电源配置,可重定义
typedef struct {
    uint8_t    evp;//电源等级
}EVO_T(POWER);


//EVO_LINK 默认的连接下级设备
typedef struct {
    ev_obj_t      *obj;//嵌套其他设备 W25WXX
    ev_drive_t    *drive;//芯片驱动 GPIO,SPI
}EVO_T(LINK);


//EVO_SET_CB 默认的设置回调
typedef struct {
    ev_obj_cb_t cb;
    void *param;//传给回调
}EVO_T(SET_CB);

//EVO_LINK 默认的连接下级设备
typedef struct {
    uint8_t      clean_flag;//是否清理为适配子设备 为真会自动释放上级设备为零的未适配子设备
}EVO_T(ADAPT);//自适应成功返回0

//EVO_LINK 默认的连接下级设备
typedef struct {
    ev_obj_t      *obj;//需要检测是否支持这个设备，支持返回0
}EVO_T(SUPPORT);


//INIT 初始化设备
typedef struct {
    uint8_t      no_arg;
}EVO_T(INIT);

//--------------------------------
//事件类型edev event -> eve
#define EVE_T(EVE_E) EVE_E##_ARG_T

enum{
    EVE_STARE = 0,    //设备事件开始
};//最多支持65535-EVE_STARE个，没必要考虑更多的情况



#endif
