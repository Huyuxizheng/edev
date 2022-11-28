#include "./core/ev_core.h"
#include "./obj/flash/ev_flash.h"
#include "./obj/flash/nor_flash/ev_w25qxx.h"
#include "./obj/flash/nor_flash/ev_w25qxx_def.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,HELP);


    return 0;
}


EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,INIT);


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_INFO)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_INFO);



    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_WRITE);


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_READ);


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_ERASE);


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,UNINIT);


    return 0;
}
EV_MODEL_LIST_DEF(ev_w25qxx_spi_m,HELP,INIT,FLASH_WRITE,FLASH_READ,FLASH_ERASE,UNINIT);

const ev_model_t ev_w25qxx_spi_m = EV_MODEL_DEF(ev_w25qxx_spi_m);

