
#include "./core/ev_core.h"
#include "./obj/drive/ev_adc.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_adc_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_adc_m,HELP);
    return 0;
}


EV_MODEL_FUN_DEF(ev_adc_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_adc_m,INIT);
    if(attr->init)
    {
        attr->init(attr->handle,attr->channel);
    }
    return 0;
}

EV_MODEL_FUN_DEF(ev_adc_m,ADC_GET_mV)
{
    EV_MODEL_FUN_GET_ARG(ev_adc_m,ADC_GET_mV);
    if(attr->get && attr->res)
    {
        (*arg->out_mv) = (float)(attr->get(attr->handle,attr->channel) *  attr->ref_mv) / (float)attr->res;
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_adc_m,ADC_GET)
{
    EV_MODEL_FUN_GET_ARG(ev_adc_m,ADC_GET);
    if(attr->get)
    {
        (*arg->out_v) = (float)(attr->get(attr->handle,attr->channel) *  attr->ref_mv) / 1000.0 / (float)attr->res;
    }

    return 0;
}


EV_MODEL_FUN_DEF(ev_adc_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_adc_m,UNINIT);
    if(attr->uninit)
    {
        attr->uninit(attr->handle,attr->channel);
    }
    return 0;
}

EV_MODEL_LIST_DEF(ev_adc_m,HELP,INIT,ADC_GET_mV,ADC_GET,UNINIT);

const ev_model_t ev_adc_m = EV_MODEL_DEF(ev_adc_m);
