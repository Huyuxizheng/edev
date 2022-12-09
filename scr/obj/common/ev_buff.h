#ifndef __EDEV_BUFF_H__
#define __EDEV_BUFF_H__

#include "./core/ev_core.h"
#include "./obj/common/ev_heap.h"


//用于大块区域缓存共用，使用前需要先获得（TAKE），结束后释放（GIVE），以保证不会因为碎片申请失败，
//释放（GIVE）后堆将清除（FREE）所有数据


enum{//方法列表
    EVO_E(BUFF_TAKE) = EVO_E(FREE)+1,
    EVO_E(BUFF_GIVE),
};


//当前的obj指针，sub自身的子对象obj（用于提供裸机中断的保护，方案一不支持）
EV_FUN_DEF(BUFF_TAKE,void * self,uint8_t sub_num,void * sub);

EV_FUN_DEF(BUFF_GIVE,void * self);



//方案1 - 裸机 中断 不受保护
extern const ev_model_t ev_buff1_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头

    ev_obj_t            *heap;//堆
    void*               *master;//用于记录最顶层obj指针
    void *              *buff_lock;
}EVO_ATTR_T(ev_buff1_m);

#define ev_buff1_m_attr_init  .master = EV_TO_RAM(void *,0),.buff_lock = EV_TO_RAM(void*,0),




#endif