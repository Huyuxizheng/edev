#include "./core/ev_core.h"
#include "./obj/drive/ev_spi.h"
#include "./obj/drive/ev_gpio.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_spi_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,HELP);


    return 0;
}


EV_MODEL_FUN_DEF(ev_spi_m,SPI_INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_INIT);

    if(arg->cs_io)
    {
        _ev_do(self,SPI_INIT_CS,arg->cs_io);
    }

    if(attr->init)
    {
        attr->init(attr->handle,arg->mode,arg->max_Mhz);
    }

    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,SPI_INIT_CS)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_INIT_CS);

    if(arg->cs_io)
    {
        _ev_do(arg->cs_io,GPIO_INIT,EV_GPIO_MODE_OUT);
        _ev_do(arg->cs_io,GPIO_SET,1);
    }

    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,SPI_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_WRITE);
    if(attr->write && arg->data && arg->size)
    {
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,0);
        }
        attr->write(attr->handle,arg->data,arg->size);
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,1);
        }
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_spi_m,SPI_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_READ);
    if(attr->read && arg->data && arg->size)
    {        
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,0);
        }
        attr->read(attr->handle,arg->data,arg->size);
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,1);
        }
    }

    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,SPI_WRITE_THEN_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_WRITE_THEN_WRITE);
    if(attr->write && ((arg->data1 && arg->size1) || (arg->data2 && arg->size2)))
    {        
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,0);
        }
        if((arg->data1 && arg->size1))
        {attr->write(attr->handle,arg->data1,arg->size1);}
        if((arg->data2 && arg->size2))
        {attr->write(attr->handle,arg->data2,arg->size2);}
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,1);
        }
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_spi_m,SPI_WRITE_THEN_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_WRITE_THEN_READ);
    if((attr->write && (arg->data1 && arg->size1)) || (attr->read && (arg->data2 && arg->size2)))
    {        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,0);
        }
        if(attr->write && (arg->data1 && arg->size1))
        {attr->write(attr->handle,arg->data1,arg->size1);}
        if(attr->read && (arg->data2 && arg->size2))
        {attr->read(attr->handle,arg->data2,arg->size2);}
        if(arg->cs_io)
        {
            _ev_do(arg->cs_io,GPIO_SET,1);
        }
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_spi_m,SPI_CMD)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_CMD);

    uint8_t size = 0;
    uint8_t data[4] = {0};
    switch(arg->cmd_size)
    {
        case 4:
            data[size++] = (arg->cmd >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->cmd >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->cmd >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->cmd  & 0x0ff;
    }

    _ev_do(self,SPI_WRITE,arg->cs_io,data,size);

    return 0;
}

EV_MODEL_FUN_DEF(ev_spi_m,SPI_CMD_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_CMD_WRITE);

    uint8_t size = 0;
    uint8_t data[8] = {0};
    switch(arg->cmd_size)
    {
        case 4:
            data[size++] = (arg->cmd >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->cmd >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->cmd >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->cmd  & 0x0ff;
    }

    if(arg->dummy && (arg->dummy < 4))
    {
        size += arg->dummy;
    }

    _ev_do(self,SPI_WRITE_THEN_WRITE,arg->cs_io,data,size,arg->data,arg->size);
    
    return 0;
}


EV_MODEL_FUN_DEF(ev_spi_m,SPI_CMD_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_CMD_READ);

    uint8_t size = 0;
    uint8_t data[8] = {0};
    switch(arg->cmd_size)
    {
        case 4:
            data[size++] = (arg->cmd >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->cmd >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->cmd >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->cmd  & 0x0ff;
    }


    if(arg->dummy && (arg->dummy < 4))
    {
        size += arg->dummy;
    }
    
    _ev_do(self,SPI_WRITE_THEN_READ,arg->cs_io,data,size,arg->data,arg->size);
    
    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,SPI_MEM_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_MEM_WRITE);

    uint8_t size = 0;
    uint8_t data[12] = {0};
    switch(arg->cmd_size)
    {
        case 4:
            data[size++] = (arg->cmd >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->cmd >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->cmd >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->cmd  & 0x0ff;
    }

    switch(arg->addr_size)
    {
        case 4:
            data[size++] = (arg->addr >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->addr >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->addr >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->addr  & 0x0ff;
    }

    if(arg->dummy && (arg->dummy < 4))
    {
        size += arg->dummy;
    }

    _ev_do(self,SPI_WRITE_THEN_WRITE,arg->cs_io,data,size,arg->data,arg->size);
    
    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,SPI_MEM_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_MEM_READ);

    uint8_t size = 0;
    uint8_t data[12] = {0};
    switch(arg->cmd_size)
    {
        case 4:
            data[size++] = (arg->cmd >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->cmd >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->cmd >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->cmd  & 0x0ff;
    }

    switch(arg->addr_size)
    {
        case 4:
            data[size++] = (arg->addr >> 24) & 0x0ff;
        case 3:
            data[size++] = (arg->addr >> 16) & 0x0ff;
        case 2:
            data[size++] = (arg->addr >> 8) & 0x0ff;
        case 1:
            data[size++] = arg->addr  & 0x0ff;
    }


    if(arg->dummy && (arg->dummy < 4))
    {
        size += arg->dummy;
    }

    _ev_do(self,SPI_WRITE_THEN_WRITE,arg->cs_io,data,size,arg->data,arg->size);
    
    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,UNINIT);

    if(attr->uninit)
    {
        attr->uninit(attr->handle);
    }

    return 0;
}
EV_MODEL_LIST_DEF(ev_spi_m,HELP,
                SPI_INIT,SPI_INIT_CS,SPI_WRITE,SPI_READ,
                SPI_WRITE_THEN_WRITE,SPI_WRITE_THEN_READ,
                SPI_CMD,SPI_CMD_WRITE,SPI_CMD_READ,
                SPI_MEM_WRITE,SPI_MEM_READ,
                UNINIT);

const ev_model_t ev_spi_m = EV_MODEL_DEF(ev_spi_m);
