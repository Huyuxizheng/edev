#ifndef __EDEV_TP_GT9147_H__
#define __EDEV_TP_GT9147_H__



typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头
    const ev_obj_t      *i2c;
    const ev_obj_t      *rst_io;
    const ev_obj_t      *isr_io;
}EVO_ATTR_T(ev_tp_gt9147_m);
#define ev_tp_gt9147_model_attr_init 

extern const ev_model_t ev_tp_gt9147_m;




#endif
