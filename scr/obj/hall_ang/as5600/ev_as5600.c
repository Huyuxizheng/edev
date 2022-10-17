#include "./obj/hall_ang/ev_hall_ang.h"
#include "./obj/hall_ang/as5600/ev_as5600.h"
#include "./obj/drive/ev_i2c.h"
#include "edev_config.h"

#define AS5600_RAW_ADDR    0x6c

#define AS5600_RAW_ANGLE_REGISTER  0x0C

EV_MODEL_FUN_DEF(ev_as5600_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_as5600_m,HELP);
/*
                                   
*/

    return 0;
}


EV_MODEL_FUN_DEF(ev_as5600_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_as5600_m,INIT);
    uint8_t ret = 0;


    if(attr->i2c)
    {
        uint8_t dat[5] = {0};
        ret |= _ev_obj_fun(attr->i2c,I2C_INIT,400);   
        ret |= _ev_obj_fun(attr->i2c,I2C_MEM_READ,AS5600_RAW_ADDR,AS5600_RAW_ANGLE_REGISTER,1,dat,2);
    }

    return ret;
}


EV_MODEL_FUN_DEF(ev_as5600_m,HALL_ANG_GET)
{
    EV_MODEL_FUN_GET_ARG(ev_as5600_m,HALL_ANG_GET);


    if(attr->i2c)
    {
        uint8_t dat[5] = {0};
        uint16_t raw_ang = 0;
        _ev_obj_fun(attr->i2c,I2C_MEM_READ,AS5600_RAW_ADDR,AS5600_RAW_ANGLE_REGISTER,1,dat,2);

        raw_ang = ((dat[0]<<8)&0x0f00) | dat[1];

        *(arg->angle) = (360.0 * ((float)raw_ang))/4096.0;
        return 0;   
    }
    *(arg->angle) = 0;
    return 1;
}


EV_MODEL_FUN_DEF(ev_as5600_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_as5600_m,UNINIT);

    if(attr->i2c)
    {
        return _ev_obj_fun(attr->i2c,UNINIT);   
    }

    return 1;
}


EV_MODEL_LIST_DEF(ev_as5600_m,HELP,INIT,HALL_ANG_GET,UNINIT);

const ev_model_t ev_as5600_m = EV_MODEL_DEF(ev_as5600_m);






