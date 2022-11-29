#include "./core/ev_core.h"
#include "./obj/flash/ev_flash.h"
#include "./obj/flash/nor_flash/ev_w25qxx.h"
#include "./obj/flash/nor_flash/ev_w25qxx_def.h"
#include "./obj/drive/ev_spi.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,HELP);


    return 0;
}


EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,INIT);

    if(attr->spi)
    {
        __ev_parent_do(self, INIT, arg);
        if(_ev_do(attr->spi,SPI_INIT,EV_SPI_MODE_3,133,attr->cs_io) == 1)
        {
            return 1;
        }
        uint8_t data[4] = {0};
        _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_DEVICE_ID,1,3,data,2);
        if(data[0] == 0xef)
        {
            return 0;
        }
    }
    return 1;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_INFO)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_INFO);



    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_WRITE);
    if(!attr->spi)
    {
        return 1;
    }
    uint8_t flash_r1 = 0xff;
    uint32_t timeout = 0;
    while (1)
    {
        _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_READ_STATUS_R1,1,0,&flash_r1,1);
        if((flash_r1 & 0x01) == 0)
        {
            break;
        }
        timeout++;
        if(timeout > 10000)
        {
            return 1;
        }
        ev_sleep(1);
    }
    


    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);


    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_PAGE_PROGRAM,1,
            arg->offset,3,
            0,arg->data,arg->size);

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_READ);
    if(!attr->spi)
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_FAST_READ,1,
            arg->offset,3,
            1,arg->data,arg->size);
    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_ERASE);

    if(!attr->spi)
    {
        return 1;
    }

    for(uint32_t i = 0;i < arg->num;i++)
    {
        uint8_t flash_r1 = 0xff;
        uint32_t timeout = 0;
        while (1)
        {
            _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_READ_STATUS_R1,1,0,&flash_r1,1);
            if((flash_r1 & 0x01) == 0)
            {
                break;
            }
            timeout++;
            if(timeout > 10000)
            {
                return 1;
            }
            ev_sleep(1);
        }

        _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

        _ev_do(attr->spi,SPI_MEM_WRITE,
                attr->cs_io,CMD_SECTOR_ERASE,1,
                arg->offset + (i * 4096),3,
                0,0,0);
    }


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,UNINIT);


    return 0;
}
EV_MODEL_LIST_DEF(ev_w25qxx_spi_m,HELP,INIT,FLASH_WRITE,FLASH_READ,FLASH_ERASE,UNINIT);

const ev_model_t ev_w25qxx_spi_m = EV_MODEL_DEF(ev_w25qxx_spi_m);

