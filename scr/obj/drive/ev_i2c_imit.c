
#include "./core/ev_core.h"
#include "./obj/drive/ev_i2c_imit.h"
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



    return 0;
}



EV_TYPE_LIST_DEF(ev_i2c_imit_type,HELP,INIT);

const ev_type_t ev_i2c_imit_type = EV_TYPE_DEF(ev_i2c_imit_type);

