
#include "./core/ev_core.h"
#include "./obj/drive/ev_i2c_imit.h"
#include "./obj/drive/ev_gpio.h"
#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_i2c_imit_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,HELP);
/*
 
    ev_obj_s *i2c_imit = ev_obj_forge(ev_i2c_imit_type, 
                                            .sda_io = &gpio_1,
                                            .scl_io = &gpio_2,
                                        );
                                      
*/

    return 0;
}

EV_TYPE_FUN_DEF(ev_i2c_imit_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,INIT);

    if(attr->sda && attr->scl)
    {
        _ev_objs_fun(attr->sda,attr->scl,GPIO_INIT_OD,());
        return 0;
    }

    return 1;
}
EV_TYPE_FUN_DEF(ev_i2c_imit_type,I2C_WRITE)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,I2C_WRITE);


    return 0;
}

EV_TYPE_FUN_DEF(ev_i2c_imit_type,I2C_READ)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,I2C_READ);


    return 0;
}

EV_TYPE_FUN_DEF(ev_i2c_imit_type,I2C_MEM_WRITE)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,I2C_MEM_WRITE);


    return 0;
}

EV_TYPE_FUN_DEF(ev_i2c_imit_type,I2C_MEM_READ)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,I2C_MEM_READ);


    return 0;
}

EV_TYPE_FUN_DEF(ev_i2c_imit_type,UNINIT)
{
    EV_TYPE_FUN_GET_ARG(ev_i2c_imit_type,INIT);



    return 0;
}

EV_TYPE_LIST_DEF(ev_i2c_imit_type,HELP,INIT,I2C_WRITE,I2C_READ,I2C_MEM_WRITE,I2C_MEM_READ,UNINIT);

const ev_type_t ev_i2c_imit_type = EV_TYPE_DEF(ev_i2c_imit_type);

