#include "./core/ev_core.h"
#include "./obj/flash/ev_flash.h"
#include "./obj/flash/ev_nand.h"
#include "./obj/flash/nand_flash/ev_w25nxx.h"
#include "./obj/flash/nand_flash/ev_w25nxx_def.h"
#include "./obj/drive/ev_spi.h"
#include "./obj/common/ev_buff.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,HELP);

    return 0;
}

static uint8_t wait_busy_10us(const ev_obj_t *cs_io,const ev_obj_t *spi)
{
    uint8_t flash_r3 = 0xff;
    uint32_t timeout = 0;
    while (1)
    {
        _ev_do(spi,SPI_CMD_READ,cs_io,CMD_READ_STATUS_R3,2,0,&flash_r3,1);
        if((flash_r3 & 0x01) == 0)
        {
            return 0;
        }
        timeout++;
        if(timeout > 1000000)
        {
            return 1;
        }
        ev_sleep_us(10);
    }    
}

static uint8_t wait_busy_100us(const ev_obj_t *cs_io,const ev_obj_t *spi)
{
    uint8_t flash_r3 = 0xff;
    uint32_t timeout = 0;
    while (1)
    {
        _ev_do(spi,SPI_CMD_READ,cs_io,CMD_READ_STATUS_R3,2,0,&flash_r3,1);
        if((flash_r3 & 0x01) == 0)
        {
            return 0;
        }
        timeout++;
        if(timeout > 100000)
        {
            return 1;
        }
        ev_sleep_us(100);
    }    
}

static uint8_t wait_busy_500us(const ev_obj_t *cs_io,const ev_obj_t *spi)
{
    uint8_t flash_r3 = 0xff;
    uint32_t timeout = 0;
    while (1)
    {
        _ev_do(spi,SPI_CMD_READ,cs_io,CMD_READ_STATUS_R3,2,0,&flash_r3,1);
        if((flash_r3 & 0x01) == 0)
        {
            return 0;
        }
        timeout++;
        if(timeout > 20000)
        {
            return 1;
        }
        ev_sleep_us(500);
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
        if(wait_busy_100us(attr->cs_io,attr->spi))
        {
            return 1;
        }
        uint8_t data[4] = {0};
        

        _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_DEVICE_ID,1,1,data,3);
        if(data[0] == 0xef)
        {
            _ev_do(attr->spi,SPI_CMD_WRITE,attr->cs_io,0xff,1,0,0,0);
            _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_READ_STATUS_R2,2,0,data,1);
            data[0] |= 0x18; 
            _ev_do(attr->spi,SPI_CMD_WRITE,attr->cs_io,CMD_WRITE_STATUS_R2,2,0,data,1);

            data[0] = 0x00; 
            _ev_do(attr->spi,SPI_CMD_WRITE,attr->cs_io,CMD_WRITE_STATUS_R1,2,0,data,1);

            return 0;
        }
    }
    return 1;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_INFO)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_INFO);

    arg->info->page_gran = 2048;
    arg->info->block_size = 128*1024;
    arg->info->oob_size = 16;
    arg->info->noob_size = 14;

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_WRITE);
    if(!attr->spi)
    {
        return 1;
    }

    if((!(arg->data && arg->size)) && (!(arg->oob_data && arg->oob_size)))
    {//没有要写入的
        return 0;
    }

    //限制大小
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

    //写入数据到缓冲区
    if(arg->data && size)
    {
        if(wait_busy_10us(attr->cs_io,attr->spi))
        {
            return 1;
        }
        _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

        _ev_do(attr->spi,SPI_MEM_WRITE,
                attr->cs_io,CMD_LOAD_PROGRAM,1,
                0,2,
                0,arg->data,size);
    }

    //写入oob数据到缓冲区（受ECC保护的）
    if(arg->oob_data && oob_size)
    {
        uint8_t oob[52] = {0};
        uint8_t oob_i = 0;
        for(int i = 0; i < 52; i++)
        {
            if((oob_i < oob_size) && (((oob_i/4)*12 + oob_i) == i))
            {
                oob[i] = arg->oob_data[oob_i];
                oob_i++;
            }
            else
            {
                oob[i] = 0xff;
            }
        }

        if(wait_busy_10us(attr->cs_io,attr->spi))
        {
            return 1;
        }
        _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

        if(arg->data && size)
        {
            _ev_do(attr->spi,SPI_MEM_WRITE,
                    attr->cs_io,CMD_RANDOM_LOAD_PROGRAM,1,
                    2048+4,2,
                    0,oob,52);
        }
        else
        {
            _ev_do(attr->spi,SPI_MEM_WRITE,
                    attr->cs_io,CMD_LOAD_PROGRAM,1,
                    2048+4,2,
                    0,oob,52);
        }
    }
        
    //写入数据
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);
    
    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_PROGRAM_EXECUTE,1,
            arg->page_offset,3,
            0,0,0);
    if(wait_busy_100us(attr->cs_io,attr->spi))
    {
        return 1;
    }

    //读出数据，检查硬件ECC
    uint8_t ret = 0;
    if(attr->buff)
    {//使用缓冲
        uint8_t *buf = 0;
        uint8_t buf_oob[16] = {0};
        _ev_do(attr->buff,BUFF_TAKE,self);

        _ev_do(attr->buff,MALLOC,&buf,2048);

        ret = _ev_do(self,NAND_READ,arg->page_offset,buf,2048,buf_oob,16);

        _ev_do(attr->buff,BUFF_GIVE,self);

        if(ret)
        {
            //硬件ECC失败
            return 1;
        }
    }
    else
    {//使用栈
        uint8_t buf[2048] = {0};
        uint8_t buf_oob[16] = {0};

        ret = _ev_do(self,NAND_READ,arg->page_offset,buf,2048,buf_oob,16);

        if(ret)
        {
            //硬件ECC失败
            return 1;
        }
    }


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_READ);
    if(!attr->spi)
    {
        return 1;
    }
    //限制尺寸
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

    //读取数据到缓存
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_READ_PAGE,1,
            arg->page_offset,3,
            0,0,0);

    //读出数据
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    if(arg->data && size)
    {
        _ev_do(attr->spi,SPI_MEM_READ,
                attr->cs_io,CMD_FAST_READ,1,
                0,2,
                1,arg->data,size);
    }

    if(arg->oob_data && oob_size)
    {
        uint8_t oob[52] = {0};
        _ev_do(attr->spi,SPI_MEM_READ,
                attr->cs_io,CMD_FAST_READ,1,
                2048+4,2,
                1,oob,52);
                
        
        for(int i = 0; i < oob_size; i++)
        {
            arg->oob_data[i] = oob[(i/4)*12 + i];
        }
    }

    uint8_t data[2] = {0};
    //检查硬件ECC标志位
    _ev_do(attr->spi,SPI_CMD_READ,attr->cs_io,CMD_READ_STATUS_R3,2,0,data,1);

    if(data[0] & 0x30)
    {
        return 1;
    }

    return 0;
}


static uint8_t erase_verify(const ev_obj_t *cs_io,const ev_obj_t *spi,uint32_t page_offset)
{
    uint8_t buf[2048 + 64] = {0};

    for(int i = 0 ; i < 64 ; i++)
    {
        //读取数据到缓存
        if(wait_busy_10us(cs_io,spi))
        {
            return 1;
        }
        _ev_do(spi,SPI_MEM_READ,
                cs_io,CMD_READ_PAGE,1,
                page_offset+i,3,
                0,0,0);

        //读出数据
        if(wait_busy_10us(cs_io,spi))
        {
            return 1;
        }

        _ev_do(spi,SPI_MEM_READ,
                cs_io,CMD_FAST_READ,1,
                0,2,
                1,buf,2048+64);

        for(int i = 0; i < (2048+64);i++)
        {
            if(buf[i] != 0xff)
            {
                return 1;
            }
        }

    }

}

static uint8_t erase_verify_buff(const ev_obj_t *cs_io,const ev_obj_t *spi,const ev_obj_t *self,const ev_obj_t *buff,uint32_t page_offset)
{
    
    uint8_t *buf = 0;
    
    if(wait_busy_500us(cs_io,spi))
    {
        return 1;
    }

    if(!buff)
    {
        return erase_verify(cs_io,spi,page_offset);
    }

    _ev_do(buff,BUFF_TAKE,self);

    _ev_do(buff,MALLOC,&buf,2048+64);

    if(!buf)
    {
        _ev_do(buff,BUFF_GIVE,self);
        return erase_verify(cs_io,spi,page_offset);
    }

    for(int i = 0 ; i < 64 ; i++)
    {
        //读取数据到缓存
        _ev_do(spi,SPI_MEM_READ,
                cs_io,CMD_READ_PAGE,1,
                page_offset+1,3,
                0,0,0);

        //读出数据
        if(wait_busy_10us(cs_io,spi))
        {
            return 1;
        }

        _ev_do(spi,SPI_MEM_READ,
                cs_io,CMD_FAST_READ,1,
                0,2,
                1,buf,2048+64);

        for(int i = 0; i < (2048+64);i++)
        {
            if(buf[i] != 0xff)
            {
                _ev_do(buff,BUFF_GIVE,self);
                return 1;
            }
        }

    }

    _ev_do(buff,BUFF_GIVE,self);
    return 0;

}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_ERASE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_ERASE);

    if(!attr->spi)
    {
        return 1;
    }
    
    //擦除块
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);

    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_BLOCK_ERASE,1,
            arg->page_offset,3,
            0,0,0);

    //校验
    return erase_verify_buff(attr->cs_io,attr->spi,self,attr->buff,(arg->page_offset&0xffffffc0));
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_CHECK_BAD_BLOCK)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_CHECK_BAD_BLOCK);

    if(!attr->spi)
    {
        return 1;
    }

    uint32_t page_offset = (arg->page_offset & 0xffffffc0);

    uint8_t data[4] = {0};

    //读取数据到缓存
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_READ_PAGE,1,
            page_offset,3,
            0,0,0);

    //读出数据
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }

    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_FAST_READ,1,
            2048,2,
            1,data,2);

    if((data[0] != 0xff) || (data[1] != 0xff))
    {
        return 1;
    }
    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_SET_BAD_BLOCK)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_SET_BAD_BLOCK);

    if(!attr->spi)
    {
        return 1;
    }
    uint32_t page_offset = (arg->page_offset & 0xffffffc0);

    uint8_t data[4] = {0};

    //读取数据到缓存
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_READ_PAGE,1,
            page_offset,3,
            0,0,0);

    //读出数据
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }

    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_FAST_READ,1,
            2048,2,
            1,data,2);

    if((data[0] != 0xff) || (data[1] != 0xff))
    {
        return 1;
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_NOOB_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_NOOB_READ);

    if(!attr->spi)
    {
        return 1;
    }
    if(!(arg->oob_data && arg->oob_size))
    {
        return 0;
    }
    //限制尺寸
    uint16_t oob_size = arg->oob_size;

    if(oob_size > 14)
    {
        oob_size = 14;
    }

    //读取数据到缓存
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_READ_PAGE,1,
            arg->page_offset,3,
            0,0,0);

    //读出数据
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }

    uint8_t oob[50] = {0};
    _ev_do(attr->spi,SPI_MEM_READ,
            attr->cs_io,CMD_FAST_READ,1,
            2048+2,2,
            1,oob,50);
            
    
    for(int i = 0; i < oob_size; i++)
    {
        arg->oob_data[i] = oob[(i+2/4)*12 + i];
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,NAND_NOOB_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,NAND_NOOB_WRITE);

    if(!attr->spi)
    {
        return 1;
    }


    if(!(arg->oob_data && arg->oob_size))
    {//没有要写入的
        return 0;
    }

    //限制大小
    uint16_t oob_size = arg->oob_size;

    if(oob_size > 14)
    {
        oob_size = 14;
    }

    //写入oob数据到缓冲区
    uint8_t oob[50] = {0};
    uint8_t oob_i = 0;
    for(int i = 0; i < 52; i++)
    {
        if((oob_i < oob_size) && ((((oob_i+2)/4)*12 + oob_i) == i))
        {
            oob[i] = arg->oob_data[oob_i];
            oob_i++;
        }
        else
        {
            oob[i] = 0xff;
        }
    }
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);


    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_LOAD_PROGRAM,1,
            2048+2,2,
            0,oob,50);
        
    //写入数据
    if(wait_busy_10us(attr->cs_io,attr->spi))
    {
        return 1;
    }
    _ev_do(attr->spi,SPI_CMD,attr->cs_io,CMD_WRITE_ENABLE,1);
    
    _ev_do(attr->spi,SPI_MEM_WRITE,
            attr->cs_io,CMD_PROGRAM_EXECUTE,1,
            arg->page_offset,3,
            0,0,0);
    if(wait_busy_100us(attr->cs_io,attr->spi))
    {
        return 1;
    }

    uint8_t buf_oob[16] = {0};
    _ev_do(self,NAND_NOOB_READ,arg->page_offset,buf_oob,14);
    for(int i = 0; i < oob_size; i++)
    {
        if(buf_oob[i] != arg->oob_data[i])
        {
            return 1;
        }
    }


    return 0;
}

EV_MODEL_FUN_DEF(ev_w25nxx_ecc_spi_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_w25nxx_ecc_spi_m,UNINIT);

    if(attr->spi)
    {
        _ev_do(attr->spi,UNINIT);
    }

    return 0;
}
EV_MODEL_LIST_DEF(ev_w25nxx_ecc_spi_m,HELP,INIT,NAND_WRITE,NAND_READ,NAND_ERASE,NAND_INFO,NAND_CHECK_BAD_BLOCK,NAND_SET_BAD_BLOCK,NAND_NOOB_WRITE,NAND_NOOB_READ,UNINIT);

const ev_model_t ev_w25nxx_ecc_spi_m = EV_MODEL_DEF(ev_w25nxx_ecc_spi_m);


