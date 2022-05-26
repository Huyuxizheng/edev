#ifndef __EDEV_TP_H__
#define __EDEV_TP_H__

/*
触摸驱动
*/


#include "./core/ev_core.h"

enum{
    EVO_E(TP_GET) = EVO_E(STARE),
};

//EVD_TP_GET
typedef struct{
    uint16_t x;
    uint16_t y;
    uint32_t tick;
    uint8_t  statie;
}EVO_S(TP_GET_OUT);

typedef struct {
    EVO_S(TP_GET_OUT) *out;
}EVO_S(TP_GET);


extern const ev_type_s ev_dri_type;





#endif
