
#include "./core/ev_core.h"
#include "./obj/drive/ev_i2c.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_i2c_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,HELP);
/*
 
    ev_obj_s *i2c = ev_obj_forge(ev_i2c_m, 
                                    .sda_io = &gpio_1,
                                    .scl_io = &gpio_2,
                                    );
                                      
*/

    return 0;
}


EV_MODEL_FUN_DEF(ev_i2c_m,I2C_INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,I2C_INIT);

    if(attr->init)
    {
        attr->init(attr->handle,arg->max_khz);
    }

    return 0;
}
EV_MODEL_FUN_DEF(ev_i2c_m,I2C_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,I2C_WRITE);
    if(attr->write)
    {
        attr->write(attr->handle,arg->addr,arg->data,arg->size,arg->no_stop);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_i2c_m,I2C_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,I2C_READ);
    if(attr->read)
    {
        attr->read(attr->handle,arg->addr,arg->data,arg->size,arg->no_stop);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_i2c_m,I2C_MEM_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,I2C_MEM_WRITE);
    if(attr->write)
    {
        attr->write(attr->handle,arg->addr,(uint8_t *)&(arg->mem_addr),arg->mem_addr_size,1);
        attr->write(attr->handle,arg->addr,arg->data,arg->size,0);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_i2c_m,I2C_MEM_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,I2C_MEM_READ);
    if(attr->read)
    {
        attr->read(attr->handle,arg->addr,(uint8_t *)&(arg->mem_addr),arg->mem_addr_size,1);
        attr->read(attr->handle,arg->addr,arg->data,arg->size,0);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_i2c_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_m,UNINIT);

    if(attr->uninit)
    {
        attr->uninit(attr->handle);
    }

    return 0;
}
EV_MODEL_LIST_DEF(ev_i2c_m,HELP,I2C_INIT,I2C_WRITE,I2C_READ,I2C_MEM_WRITE,I2C_MEM_READ,UNINIT);

const ev_model_t ev_i2c_m = EV_MODEL_DEF(ev_i2c_m);
