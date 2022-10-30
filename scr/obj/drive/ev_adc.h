#ifndef __EDEV_ADC_H__
#define __EDEV_ADC_H__



#include "./core/ev_core.h"



enum{
    EVO_E(ADC_GET_mV) = EVO_E(START),
    EVO_E(ADC_GET) = EVO_E(START),
};



EV_FUN_DEF(ADC_GET_mV,float *out_mv);

EV_FUN_DEF(ADC_GET,float *out_v);




extern const ev_model_t ev_adc_m;

typedef struct{//属性列表
    ev_obj_attr_base_t  base;//固定头    //可选的 GPIO组

    void*               handle;
    uint32_t            channel;

    uint32_t            ref_mv;     //参考电压 mv
    uint32_t            res;        //分辨率

    uint8_t     (*init)(void* handle,uint32_t channel);
    uint32_t    (*get)(void* handle,uint32_t channel);  //获得ADC原始值
    uint8_t     (*uninit)(void* handle,uint32_t channel);
    
}EVO_ATTR_T(ev_adc_m);
#define ev_adc_m_attr_init 

#endif
