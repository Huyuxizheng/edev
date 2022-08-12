#include "./core/ev_core.h"
#include "./obj/drive/ev_spi.h"
#include "edev_config.h"


EV_TYPE_FUN_DEF(ev_spi_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_spi_type,HELP);


    return 0;
}


EV_TYPE_FUN_DEF(ev_spi_type,SPI_INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_spi_type,SPI_INIT);

    if(attr->init)
    {
        attr->init(attr->handle,arg->mode,arg->speed_M);
    }

    return 0;
}
EV_TYPE_FUN_DEF(ev_spi_type,SPI_WRITE)
{
    EV_TYPE_FUN_GET_ARG(ev_spi_type,SPI_WRITE);
    if(attr->write)
    {
        attr->write(attr->handle,arg->data,arg->size);
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_spi_type,SPI_READ)
{
    EV_TYPE_FUN_GET_ARG(ev_spi_type,SPI_READ);
    if(attr->read)
    {
        attr->read(attr->handle,arg->data,arg->size);
    }

    return 0;
}

EV_TYPE_FUN_DEF(ev_spi_type,UNINIT)
{
    EV_TYPE_FUN_GET_ARG(ev_spi_type,UNINIT);

    if(attr->uninit)
    {
        attr->uninit(attr->handle);
    }

    return 0;
}
EV_TYPE_LIST_DEF(ev_spi_type,HELP,SPI_INIT,SPI_WRITE,SPI_READ,UNINIT);

const ev_type_t ev_spi_type = EV_TYPE_DEF(ev_spi_type);
