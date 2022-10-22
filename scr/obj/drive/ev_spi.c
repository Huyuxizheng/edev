#include "./core/ev_core.h"
#include "./obj/drive/ev_spi.h"
#include "edev_config.h"


EV_MODEL_FUN_DEF(ev_spi_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,HELP);


    return 0;
}


EV_MODEL_FUN_DEF(ev_spi_m,SPI_INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_INIT);

    if(attr->init)
    {
        attr->init(attr->handle,arg->mode,arg->max_Mhz);
    }

    return 0;
}
EV_MODEL_FUN_DEF(ev_spi_m,SPI_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_WRITE);
    if(attr->write)
    {
        attr->write(attr->handle,arg->data,arg->size);
    }

    return 0;
}

EV_MODEL_FUN_DEF(ev_spi_m,SPI_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_spi_m,SPI_READ);
    if(attr->read)
    {
        attr->read(attr->handle,arg->data,arg->size);
    }

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
EV_MODEL_LIST_DEF(ev_spi_m,HELP,SPI_INIT,SPI_WRITE,SPI_READ,UNINIT);

const ev_model_t ev_spi_m = EV_MODEL_DEF(ev_spi_m);
