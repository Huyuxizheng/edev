#ifndef __EDEV_CORE_H__
#define __EDEV_CORE_H__

#include "stdint.h"


typedef struct ev_obj_s ev_obj_s;
typedef struct ev_type_s ev_type_s;

//方法原型
typedef uint8_t (*edev_obj_fun_t)(ev_obj_s *obj,void *arg);

//自变量构造方法,成功返回0,vals成员不作为判断依据
typedef uint8_t (*edev_vals_create_t)(ev_obj_s *obj);
//自变量释放方法
typedef void (*edev_vals_free_t)(ev_obj_s *obj);

//设备类型
typedef struct ev_type_s{
    char                *name;
    edev_vals_create_t  vals_create;
    edev_vals_free_t    vals_free;

    uint16_t        total;      //方法总数
    edev_obj_fun_t  *list;       //方法清单
}ev_type_s;

//设备对象结构
typedef struct ev_obj_s{
    void            *vals;      //动态属性
    ev_type_s       *type;   //方法列表
    void            *lock;      //设备锁，可选
}ev_obj_s;

//断言-错误返回1
#define ev_obj_assert(obj) \
if(!obj){ev_warning("%s obj null\r\n",__fun__);return 1;}

#define ev_type_assert(obj) \
if(!obj->type){ev_warning("%s type null\r\n",__fun__);return 1;}

#define ev_vals_assert(obj) \
if(!obj->vals){ev_warning("%s vals null\r\n",__fun__);return 1;}

#define ev_op_assert(obj,op) \
if(op >= obj->type->total)\
{ev_warning("%s:%s no fun op:%d\r\n",__fun__,obj->type->name,op);return 1;}



//--------------------------------
//选项edev Options -> evo
#define EVO_S(EVO_E) EVO_E##_ARG_S
extern uint8_t _ev_obj_fun(ev_obj_s *obj, uint16_t op, void *arg);

//基础选项

//基础选项列表,每一个设备都需要有的选项
enum{
    EVO_HELP = 0,    //帮助信息
    EVO_STARE,       //设备方法的开始
    EVO_LINK,        //默认连接下级设备,可重定义
    EVO_SET_CB,      //默认设置回调,可重定义
};//最多支持65535-EVO_STARE个，没必要考虑更多的情况

//EVO_HELP 帮助信息 注释或打印
typedef struct {
    uint16_t op;
}EVO_S(EVO_HELP);


//EVO_LINK 默认的连接下级设备
typedef struct {
    ev_obj_s *obj;
}EVO_S(EVO_LINK);


//EVO_SET_CB 默认的设置回调
typedef void (*ev_obj_cb_t)(ev_obj_s *obj,uint16_t event,void *arg);

typedef struct {
    ev_obj_cb_t cb;
}EVO_S(EVO_SET_CB);


//--------------------------------
//事件类型
//事件edev event -> eve
#define EVE_S(EVE_E) EVE_E##_ARG_S

enum{
    EVE_STARE = 0,    //设备事件开始
};//最多支持65535-EVE_STARE个，没必要考虑更多的情况



#endif
