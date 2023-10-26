#include "./core/ev_core.h"
#include "./obj/flash/ev_flash.h"
#include "./obj/flash/nor_flash/ev_w25qxx.h"
#include "./obj/flash/nor_flash/ev_w25qxx_def.h"
#include "./obj/drive/ev_spi.h"
#include "edev_config.h"



EV_MODEL_FUN_DEF(ev_w25q32_spi_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25q32_spi_m,INIT);

    if(__ev_parent_do(self,INIT,arg))
    {
        return 1;
    }
    uint8_t data[4] = {0};
    _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_DEVICE_ID,1,3,data,2);
    if(data[1] == 0x15)
    {
        return 0;
    }
    return 1;
}

EV_MODEL_FUN_DEF(ev_w25q32_spi_m,FLASH_INFO)
{
    EV_MODEL_FUN_GET_ARG(ev_w25q32_spi_m,FLASH_INFO);

    __ev_parent_do(self,FLASH_INFO,arg);
    arg->info->size = 4*1024*1024;

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25q32_spi_m,FLASH_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25q32_spi_m,FLASH_WRITE);

    if(arg->offset > 4*1024*1024)
    {
        return 1;
    }
    if((arg->offset + arg->size) > 4*1024*1024)
    {
        return _ev_parent_do(self,FLASH_WRITE,arg->offset,arg->data,(4*1024*1024 - arg->offset));
    }

    return __ev_parent_do(self,FLASH_WRITE,arg);
}

EV_MODEL_FUN_DEF(ev_w25q32_spi_m,FLASH_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25q32_spi_m,FLASH_READ);
    if(arg->offset > 4*1024*1024)
    {
        return 1;
    }
    if((arg->offset + arg->size) > 4*1024*1024)
    {
        return _ev_parent_do(self,FLASH_READ,arg->offset,arg->data,(4*1024*1024 - arg->offset));
    }
    return __ev_parent_do(self,FLASH_READ,arg);
}

EV_MODEL_FUN_DEF(ev_w25q32_spi_m,FLASH_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25q32_spi_m,FLASH_ERASE);

    if(arg->offset > 4*1024*1024)
    {
        return 1;
    }
    if((arg->offset + (arg->num*4*1024)) > 4*1024*1024)
    {
        return _ev_parent_do(self,FLASH_ERASE,arg->offset,((4*1024*1024 - arg->offset)/(4*1024)));
    }

    return __ev_parent_do(self,FLASH_ERASE,arg);
}


EV_MODEL_LIST_DEF(ev_w25q32_spi_m,INIT,FLASH_WRITE,FLASH_READ,FLASH_ERASE,FLASH_INFO);

const ev_model_t ev_w25q32_spi_m = EV_MODEL_DEF(ev_w25q32_spi_m,ev_w25qxx_spi_m);

