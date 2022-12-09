#include "./core/ev_core.h"
#include "./obj/flash/ev_flash.h"
#include "./obj/flash/ev_nand.h"
#include "./obj/flash/nand_flash/ev_w25nxx.h"
#include "./obj/flash/nand_flash/ev_w25nxx_def.h"
#include "./obj/drive/ev_spi.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,HELP);

    return 0;
}

static uint8_t wait_busy(const ev_obj_t *cs_io,const ev_obj_t *spi)
{
    uint8_t flash_r3 = 0xff;
    uint32_t timeout = 0;
    while (1)
    {
        _ev_do(spi,SPI_CMD_READ,cs_io,CMD_READ_STATUS_R1,2,0,&flash_r3,1);
        if((flash_r3 & 0x01) == 0)
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

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,INIT);

    if(attr->spi)
    {
        if(_ev_do(attr->spi,SPI_INIT,EV_SPI_MODE_3,104,attr->cs_io) == 1)
        {
            return 1;
        }
        if(wait_busy(attr->cs_io,attr->spi))
        {
            return 1;
        }
        uint8_t data[4] = {0};
        

        _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_DEVICE_ID,1,1,data,3);
        if(data[0] == 0xef)
        {
            _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_READ_STATUS_R2,2,0,data,1);
            data[0] |= 0x18; 
            _ev_do(attr->spi,SPI_CMD_WRITE,attr->cs_io,CMD_WRITE_STATUS_R2,2,0,data,1);
            return 0;
        }
    }
    return 1;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_ECC_INFO)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_ECC_INFO);

    arg->info->page_gran = 2048;
    arg->info->block_size = 128*1024;
    arg->info->ecc_oob_size = 16;
    arg->info->oob_size = 14;

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_ECC_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_ECC_WRITE);
    if(!attr->spi)
    {
        return 1;
    }
    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }
    uint16_t size = arg->size;
    uint16_t oob_size = arg->oob_size;
    if(size > 2048)
    {
        size = 2048;
    }
    if(oob_size > 16)
    {
        oob_size = 16;
    }

    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_LOAD_PROGRAM,1,
            0,2,
            0,arg->data,size);

    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }

    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_RANDOM_LOAD_PROGRAM,1,
            2048+2,2,
            0,arg->oob_data,oob_size);
    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);
    
    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_PROGRAM_EXECUTE,1,
            attr->page_offset,3,
            0,0,0);
    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }

    uint8_t ret = 0;
    if(attr->buff)
    {
        uint8_t *buf = 0;
        uint8_t buf_oob[16] = {0};
        _ev_do(attr->buff,BUFF_TAKE,self);

        _ev_do(attr->buff,BUFF_TAKE,&buf,2048);

        ret = _ev_do(self,NAND_ECC_READ,buf,2048,buf_oob,16);

        _ev_do(attr->buff,BUFF_GIVE,self);
    }


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_ECC_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_ECC_READ);
    if(!attr->spi)
    {
        return 1;
    }
    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }

    uint16_t size = arg->size;
    uint16_t oob_size = arg->oob_size;
    if(size > 2048)
    {
        size = 2048;
    }
    if(oob_size > 16)
    {
        oob_size = 16;
    }

    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_READ_PAGE,1,
            attr->page_offset,3,
            0,0,0);

    if(wait_busy(attr->cs_io,attr->spi))
    {
        return 1;
    }
    uint8_t data[4] = {0};

    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_FAST_READ,1,
            0,2,
            4,arg->data,size);

    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_FAST_READ,1,
            2048+2,2,
            4,arg->oob_data,oob_size);

    
    _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_WRITE_STATUS_R3,2,0,data,1);

    if(data[0] & 0x30)
    {
        return 1;
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_ECC_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_ECC_ERASE);

    if(!attr->spi)
    {
        return 1;
    }


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,UNINIT);

    _ev_do(attr->spi,UNINIT);

    return 0;
}
EV_MODEL_LIST_DEF(ev_w25nxx_ecc_spi_m,HELP,INIT,FLASH_WRITE,FLASH_READ,FLASH_ERASE,UNINIT);

const ev_model_t ev_w25nxx_ecc_spi_m = EV_MODEL_DEF(ev_w25nxx_ecc_spi_m);


