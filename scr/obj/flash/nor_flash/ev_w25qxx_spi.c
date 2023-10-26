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

static uint8_t wait_busy(const ev_obj_t *cs_io,const ev_obj_t *spi)
{
    uint8_t flash_r1 = 0xff;
    uint32_t timeout = 0;
    while (1)
    {
        _ev_do(spi,SPI_CMD_READ,cs_io,CMD_READ_STATUS_R1,1,0,&flash_r1,1);
        if((flash_r1 & 0x01) == 0)
        {
            return 0;
        }
        timeout++;
        if(timeout > 10000)
        {
            return 1;
        }
        ev_sleep(1);
    }    
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,INIT);

    if(attr->spi)
    {
        if(_ev_do(attr->spi,SPI_INIT,EV_SPI_MODE_3,133,attr->cs_io) == 1)
        {
            return 1;
        }
        if(wait_busy(attr->cs_io,attr->spi))
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

    arg->info->read_gran = 256;
    arg->info->write_gran = 256;
    arg->info->erase_gran = 4096;

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_WRITE);
    if(!attr->spi)
    {
        return 1;
    }

    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }

    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

    if(arg->offset < 0x00ffffff )
    {//24位地址指令
        _ev_do(attr->spi,SPI_MEM_WRITE,
                attr->cs_io,CMD_PAGE_PROGRAM,1,
                arg->offset,3,
                0,arg->data,arg->size);
    }
    else
    {//32位地址
        _ev_do(attr->spi,SPI_MEM_WRITE,
                attr->cs_io,CMD_PAGE_PROGRAM_4A,1,
                arg->offset,4,
                0,arg->data,arg->size);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_READ);
    if(!attr->spi)
    {
        return 1;
    }
    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }
    
    if(arg->offset < 0x00ffffff )
    {//24位地址指令
        _ev_do(attr->spi,SPI_MEM_READ,
                attr->cs_io,CMD_FAST_READ,1,
                arg->offset,3,
                1,arg->data,arg->size);
    }
    else
    {//32位地址
        _ev_do(attr->spi,SPI_MEM_READ,
                attr->cs_io,CMD_FAST_READ_4A,1,
                arg->offset,4,
                1,arg->data,arg->size);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,FLASH_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,FLASH_ERASE);

    if(!attr->spi)
    {
        return 1;
    }
    if(!arg->num)
    {
        return 0;
    }
    uint32_t offset = arg->offset;
    if(((offset >> 12 )+ arg->num) < 0x00fff )
    {//24位地址指令
        for(uint32_t i = arg->num;i > 0;)
        {
            if(wait_busy(attr->cs_io,attr->spi))
            {
                return 1;
            }

            _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

            if(i < 8)
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_SECTOR_ERASE,1,
                        offset,3,
                        0,0,0);
                i--;
                offset += 1*4096;
            }
            else if( (i >= 16) && (((offset >> 12) &0x0f) == 0) )
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_ERASE_16_SECTOR,1,
                        offset,3,
                        0,0,0);
                i -= 16;
                offset += 16*4096;
            }
            else if( (i >= 8) && (((offset >> 12) &0x07) == 0) )
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_ERASE_8_SECTOR,1,
                        offset,3,
                        0,0,0);
                i -= 8;
                offset += 8*4096;
            }
            else
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_SECTOR_ERASE,1,
                        offset,3,
                        0,0,0);
                i--;
                offset += 1*4096;
            }
        }
    }
    else
    {//32位地址
        for(uint32_t i = arg->num;i > 0;)
        {
            if(wait_busy(attr->cs_io,attr->spi))
            {
                return 1;
            }

            _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

            if(i < 16)
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_SECTOR_ERASE_4A,1,
                        offset,4,
                        0,0,0);
                i--;
                offset += 1*4096;
            }
            else if( (i >= 16) && (((offset >> 12) &0x0f) == 0) )
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_ERASE_16_SECTOR_4A,1,
                        offset,4,
                        0,0,0);
                i -= 16;
                offset += 16*4096;
            }
            else
            {
                _ev_do(attr->spi,SPI_MEM_WRITE,
                        attr->cs_io,CMD_SECTOR_ERASE_4A,1,
                        offset,4,
                        0,0,0);
                i--;
                offset += 1*4096;
            }
        }
    }


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25qxx_spi_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25qxx_spi_m,UNINIT);

    _ev_do(attr->spi,UNINIT);

    return 0;
}
EV_MODEL_LIST_DEF(ev_w25qxx_spi_m,FLASH_INFO,HELP,INIT,FLASH_WRITE,FLASH_READ,FLASH_ERASE,UNINIT);

const ev_model_t ev_w25qxx_spi_m = EV_MODEL_DEF(ev_w25qxx_spi_m);

