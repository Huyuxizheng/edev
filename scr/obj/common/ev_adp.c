
#include "./core/ev_core.h"
#include "./obj/common/ev_adp.h"
#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_adp_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_adp_type,HELP);


    return 0;
}


EV_TYPE_FUN_DEF(ev_adp_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_adp_type,INIT);



    return 0;
}


EV_TYPE_LIST_DEF(ev_adp_type,HELP,INIT);

const ev_type_t ev_adp_type = EV_TYPE_DEF(ev_adp_type);
