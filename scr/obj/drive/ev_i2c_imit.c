
#include "./core/ev_core.h"
#include "./obj/drive/ev_i2c_imit.h"
#include "./obj/drive/ev_gpio.h"
#include "edev_config.h"


static void _ev_iic_imit_start(const EVO_ATTR_T(ev_i2c_imit_m) *attr)
{
    _ev_objs_fun(attr->sda,attr->scl,GPIO_SET,(1));
    ev_sleep_us(*(attr->t));
    
    _ev_obj_fun(attr->sda,GPIO_SET,0);
    ev_sleep_us(*(attr->t));
    _ev_obj_fun(attr->scl,GPIO_SET,0);
    ev_sleep_us(*(attr->t));
} 

static void _ev_iic_imit_stop(const EVO_ATTR_T(ev_i2c_imit_m) *attr)
{
    _ev_objs_fun(attr->sda,attr->scl,GPIO_SET,(0));
    ev_sleep_us(*(attr->t));
    
    _ev_obj_fun(attr->scl,GPIO_SET,1);
    ev_sleep_us(*(attr->t));
    _ev_obj_fun(attr->sda,GPIO_SET,1);
    ev_sleep_us(*(attr->t));
} 

static void _ev_iic_imit_send_ack(const EVO_ATTR_T(ev_i2c_imit_m) *attr,uint8_t ack)
{ 
    _ev_obj_fun(attr->scl,GPIO_SET,0);
    _ev_obj_fun(attr->sda,GPIO_SET,!ack);

    ev_sleep_us(*(attr->t));
    _ev_obj_fun(attr->scl,GPIO_SET,1);
    ev_sleep_us(*(attr->t));

    _ev_obj_fun(attr->scl,GPIO_SET,0);
    _ev_obj_fun(attr->sda,GPIO_SET,1);
} 

static uint8_t _ev_iic_imit_read_ack(const EVO_ATTR_T(ev_i2c_imit_m) *attr)
{ 
    uint8_t ack = 0;
    //_ev_obj_fun(attr->sda,GPIO_SET,1);

    _ev_obj_fun(attr->sda,GPIO_INIT,EV_GPIO_MODE_IN);

    ev_sleep_us(*(attr->t));
    _ev_obj_fun(attr->scl,GPIO_SET,1);
    ev_sleep_us(*(attr->t));

    ack = _ev_obj_fun(attr->sda,GPIO_GET);

    _ev_obj_fun(attr->scl,GPIO_SET,0);

    _ev_obj_fun(attr->sda,GPIO_INIT,EV_GPIO_MODE_OUT);
    _ev_obj_fun(attr->sda,GPIO_SET,1);
    return ack;
} 

static void _ev_iic_imit_send_byte(const EVO_ATTR_T(ev_i2c_imit_m) *attr,uint8_t dat)
{ 
    for(uint8_t i = 0; i < 8; i++)
    {
        _ev_obj_fun(attr->scl,GPIO_SET,0);
        ev_sleep_us(*(attr->t));
        if(dat & 0x80) 
            {_ev_obj_fun(attr->sda,GPIO_SET,1);}
        else 
        	{_ev_obj_fun(attr->sda,GPIO_SET,0);}
        _ev_obj_fun(attr->scl,GPIO_SET,1);
        dat <<= 1;				//从最高位开始传输数据
        ev_sleep_us(*(attr->t));
    }
    _ev_obj_fun(attr->scl,GPIO_SET,0);
    //_ev_obj_fun(attr->sda,GPIO_SET,1);
} 

static uint8_t _ev_iic_imit_read_byte(const EVO_ATTR_T(ev_i2c_imit_m) *attr)
{ 
    uint8_t dat;
    _ev_obj_fun(attr->sda,GPIO_INIT,EV_GPIO_MODE_IN);
    for(uint8_t i = 0; i < 8; i++)
    {
        _ev_obj_fun(attr->scl,GPIO_SET,1);
        ev_sleep_us(*(attr->t));
        dat <<= 1;
        dat |= (!!_ev_obj_fun(attr->sda,GPIO_GET));
        _ev_obj_fun(attr->scl,GPIO_SET,0);
        ev_sleep_us(*(attr->t));
    }
    _ev_obj_fun(attr->sda,GPIO_INIT,EV_GPIO_MODE_OUT);
    _ev_obj_fun(attr->sda,GPIO_SET,1);
    return dat;
} 

EV_MODEL_FUN_DEF(ev_i2c_imit_m,HELP)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,HELP);
/*
 
    ev_obj_s *i2c_imit = ev_obj_forge(ev_i2c_imit_m, 
                                            .sda_io = &gpio_1,
                                            .scl_io = &gpio_2,
                                        );
                                      
*/

    return 0;
}

EV_MODEL_FUN_DEF(ev_i2c_imit_m,I2C_INIT)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,I2C_INIT);

    if(attr->sda && attr->scl)
    {
        _ev_objs_fun(attr->sda,attr->scl,GPIO_INIT,(EV_GPIO_MODE_OUT));
        _ev_objs_fun(attr->sda,attr->scl,GPIO_SET,(1));
        
        if(arg)
        if(arg->max_khz > 2)
        {
            *(attr->t) = (5000/arg->max_khz + 9)/10;

        }
        return 0;
    }

    return 1;
}
EV_MODEL_FUN_DEF(ev_i2c_imit_m,I2C_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,I2C_WRITE);
    uint8_t ret = 0;

    _ev_iic_imit_start(attr);
    _ev_iic_imit_send_byte(attr,arg->addr & 0xfe);
    ret |= _ev_iic_imit_read_ack(attr);
    for(uint32_t i = 0; i < arg->size; i++)
    {
        _ev_iic_imit_send_byte(attr,arg->data[i]);
        ret |= _ev_iic_imit_read_ack(attr);
    }
    _ev_iic_imit_stop(attr);
    return ret;
}

EV_MODEL_FUN_DEF(ev_i2c_imit_m,I2C_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,I2C_READ);
    uint8_t ret = 0;

    _ev_iic_imit_start(attr);
    _ev_iic_imit_send_byte(attr,arg->addr | 0x01);
    ret |= _ev_iic_imit_read_ack(attr);
    for(uint32_t i = 0; i < arg->size; )
    {
        arg->data[i] = _ev_iic_imit_read_byte(attr);
        i++;
        _ev_iic_imit_send_ack(attr,(i<arg->size)?1:0);
    }
    _ev_iic_imit_stop(attr);
    return ret;
}

EV_MODEL_FUN_DEF(ev_i2c_imit_m,I2C_MEM_WRITE)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,I2C_MEM_WRITE);
    uint8_t ret = 0;

    _ev_iic_imit_start(attr);
    _ev_iic_imit_send_byte(attr,arg->addr & 0xfe);
    ret |= _ev_iic_imit_read_ack(attr);
    if(arg->mem_addr_size >= 2)
    {
        _ev_iic_imit_send_byte(attr,arg->mem_addr>>8);
        ret |= _ev_iic_imit_read_ack(attr);
    }
    _ev_iic_imit_send_byte(attr,arg->mem_addr&0xff);
    ret |= _ev_iic_imit_read_ack(attr);

    for(uint32_t i = 0; i < arg->size; i++)
    {
        _ev_iic_imit_send_byte(attr,arg->data[i]);
        ret |= _ev_iic_imit_read_ack(attr);
    }
    _ev_iic_imit_stop(attr);

    return ret;
}

EV_MODEL_FUN_DEF(ev_i2c_imit_m,I2C_MEM_READ)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,I2C_MEM_READ);
    uint8_t ret = 0;

    _ev_iic_imit_start(attr);
    _ev_iic_imit_send_byte(attr,arg->addr & 0xfe);
    ret |= _ev_iic_imit_read_ack(attr);
    if(arg->mem_addr_size >= 2)
    {
        _ev_iic_imit_send_byte(attr,arg->mem_addr>>8);
        ret |= _ev_iic_imit_read_ack(attr);
    }
    _ev_iic_imit_send_byte(attr,arg->mem_addr&0xff);
    ret |= _ev_iic_imit_read_ack(attr);

    _ev_iic_imit_start(attr);
    _ev_iic_imit_send_byte(attr,arg->addr | 0x01);
    ret |= _ev_iic_imit_read_ack(attr);
    for(uint32_t i = 0; i < arg->size; )
    {
        arg->data[i] = _ev_iic_imit_read_byte(attr);
        i++;
        _ev_iic_imit_send_ack(attr,(i<arg->size)?1:0);
    }
    _ev_iic_imit_stop(attr);

    return ret;
}

EV_MODEL_FUN_DEF(ev_i2c_imit_m,UNINIT)
{
    EV_MODEL_FUN_GET_ARG(ev_i2c_imit_m,INIT);

    _ev_objs_fun(attr->sda,attr->scl,UNINIT,());

    return 0;
}

EV_MODEL_LIST_DEF(ev_i2c_imit_m,HELP,I2C_INIT,I2C_WRITE,I2C_READ,I2C_MEM_WRITE,I2C_MEM_READ,UNINIT);

const ev_model_t ev_i2c_imit_m = EV_MODEL_DEF(ev_i2c_imit_m);

