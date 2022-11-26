#include "./core/ev_core.h"
#include "./obj/flash/ev_flash.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_flash_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,HELP);


    return 0;
}


EV_MODEL_FUN_DEF(ev_flash_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,INIT);

    if(attr->init)
    {
        attr->init();
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_flash_m,FLASH_INFO)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,FLASH_INFO);

    *(arg->info) = attr->info;


    return 0;
}

EV_MODEL_FUN_DEF(ev_flash_m,FLASH_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,FLASH_WRITE);
    if(attr->write)
    {
        attr->write(arg->offset,arg->data,arg->size);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_flash_m,FLASH_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,FLASH_READ);
    if(attr->read)
    {
        attr->read(arg->offset,arg->data,arg->size);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_flash_m,FLASH_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,FLASH_ERASE);
    if(attr->erase)
    {
        attr->erase(arg->offset,arg->num);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_flash_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_flash_m,UNINIT);

    if(attr->uninit)
    {
        attr->uninit();
    }

    return 0;
}
EV_MODEL_LIST_DEF(ev_flash_m,HELP,INIT,FLASH_WRITE,FLASH_READ,FLASH_ERASE,UNINIT);

const ev_model_t ev_flash_m = EV_MODEL_DEF(ev_flash_m);
