#include "./dev/tp/ev_tp.h"
#include "./dev/tp/gt9147/ev_tp_gt9147.h"
#include "edev_config.h"
#include "./core/ev_obj_list.h"

//GT9147配置参数表
//第一个字节为版本号(0X60),必须保证新的版本号大于等于GT9147内部
const uint8_t GT9147_CFG[]=
{ 
    0X80,0x47,//寄存器地址

	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};  

#define GT9147_ADD 		0X28     	//地址


//GT9147 寄存器定义 
#define GT_CTRL_REG 	(const uint8_t []){0X80,0x40 }  	//GT9147控制寄存器
#define GT_CFGS_REG 	(const uint8_t []){0X80,0x47}   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	(const uint8_t []){0X80,0xFF}   	//GT9147校验和寄存器
#define GT_PID_REG 		(const uint8_t []){0X81,0x40}   	//GT9147产品ID寄存器

#define GT_GSTID_REG 	(const uint8_t []){0X81,0X4E}  	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		(const uint8_t []){0X81,0X50}  	//第一个触摸点数据地址



typedef struct {
    EV_DRI_T(GPIO) *reset;
    EV_DRI_T(GPIO_INT)  *gpio_int;
    EV_DRI_T(I2C)  *i2c;
}ev_tp_gt9147_val_t;


EV_TYPE_FUN_DEF(ev_tp_gt9147_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(HELP);
/*zhon
                                   
*/

    return 0;
}


EV_TYPE_FUN_DEF(ev_tp_gt9147_type,LINK)
{
    EV_TYPE_FUN_GET_ARG(LINK);
    if(!arg->drive){return 1;}
    ev_tp_gt9147_val_t *vals = self->vals;

    switch(arg->drive->e)
    {
        case EV_DRI_E(GPIO):
            vals->reset = arg->drive->p;
        break;
        case EV_DRI_E(I2C):
            vals->i2c = arg->drive->p;
        break;
        case EV_DRI_E(GPIO_INT):
            vals->gpio_int = arg->drive->p;
        break;
    }

    return 1;
}

EV_TYPE_FUN_DEF(ev_tp_gt9147_type,POWER)
{
    EV_TYPE_FUN_GET_ARG(POWER);

    ev_tp_gt9147_val_t *vals = self->vals;

    switch(arg->evp)
    {
        case EVP_NONE:case EVP_HIGH:case EVP_OPEN:
            ev_dri_i2c_init(vals->i2c);
            ev_dri_gpio_int_init(vals->gpio_int,EV_DRI_GPIO_INT_OUT_MODE);
            ev_dri_gpio_init(vals->reset);

            ev_dri_gpio_int_set(vals->gpio_int,0);
            ev_dri_gpio_set(vals->reset,0);
            ev_sleep(5);
            ev_dri_gpio_int_set(vals->gpio_int,1);
            ev_sleep(1);
            ev_dri_gpio_set(vals->reset,1);
            ev_sleep(5);
            ev_dri_gpio_int_init(vals->gpio_int,EV_DRI_GPIO_INT_INTERRUPT_MODE);
            ev_sleep(100);

        break;
        case EVP_IDLE:case EVP_CLOSE:
            ev_dri_i2c_uninit(vals->i2c);
            ev_dri_gpio_int_uninit(vals->gpio_int);
            ev_dri_gpio_uninit(vals->reset);
        break;
    }

    return 0;
}
EV_TYPE_FUN_DEF(ev_tp_gt9147_type,SET_CB)
{
    EV_TYPE_FUN_GET_ARG(SET_CB);

    ev_tp_gt9147_val_t *vals = self->vals;

    if(arg->cb)
    {
        ev_dri_gpio_int_set_cb(vals->gpio_int,arg->cb,arg->param);
    }
    return 0;
}

EV_TYPE_FUN_DEF(ev_tp_gt9147_type,ADAPT)
{
    EV_TYPE_FUN_GET_ARG(ADAPT);

    ev_tp_gt9147_val_t *vals = self->vals;
    uint8_t id[6] = {0};

    ev_dri_i2c_write(vals->i2c,GT9147_ADD,GT_CTRL_REG,2);

    ev_dri_i2c_read(vals->i2c,GT9147_ADD,id,4);
    if(
        (
            (id[0] != '9') &&
            (id[1] != '1') &&
            (id[2] != '4') &&
            (id[3] != '7') 
        )
    )
    {
        ev_info("gt9147 read id fail\r\n");
        return 1;
    }

    ev_info("gt9147 id:%s \r\n",id);
    return 0;
}
EV_TYPE_FUN_DEF(ev_tp_gt9147_type,SUPPORT)
{
    EV_TYPE_FUN_GET_ARG(SUPPORT);

    ev_tp_gt9147_val_t *vals = self->vals;


    if(arg->obj->type == &ev_tp_type)
    {
            return 0;
    }


    return 1;
}
EV_TYPE_FUN_DEF(ev_tp_gt9147_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(TP_GET);

    ev_tp_gt9147_val_t *vals = self->vals;

    uint8_t dat[5] = {0};

    dat[0] = GT_CTRL_REG[0];
    dat[1] = GT_CTRL_REG[1];
    dat[2] = 0x02;
    ev_dri_i2c_write(vals->i2c,GT9147_ADD,dat,3);//软件复位
    ev_dri_i2c_write(vals->i2c,GT9147_ADD,GT_CFGS_REG,2);//软件复位
    ev_dri_i2c_read(vals->i2c,GT9147_ADD,dat,1);
    if(dat[0]<0X60)//默认版本比较低,需要更新flash配置
    {
        uint8_t buf[2] = {0,1};
        for(int i=2;i<sizeof(GT9147_CFG);i++)buf[0]+=GT9147_CFG[i];
        buf[0]=(~buf[0])+1;

	    ev_dri_i2c_write(vals->i2c,GT9147_ADD,GT9147_CFG,sizeof(GT9147_CFG));//发送寄存器配置

        dat[0] = GT_CHECK_REG[0];
        dat[1] = GT_CHECK_REG[1];
        dat[2] = buf[0];
        dat[3] = buf[1];
        ev_dri_i2c_write(vals->i2c,GT9147_ADD,dat,4);
    }
    ev_sleep(10);

    dat[0] = GT_CTRL_REG[0];
    dat[1] = GT_CTRL_REG[1];
    dat[2] = 0x00;
    ev_dri_i2c_write(vals->i2c,GT9147_ADD,dat,3);//复位

    return 0;
}

EV_TYPE_FUN_DEF(ev_tp_gt9147_type,TP_IC_GET)
{
    EV_TYPE_FUN_GET_ARG(TP_GET);

    ev_tp_gt9147_val_t *vals = self->vals;


    uint8_t dat[5] = {0};
    ev_dri_i2c_write(vals->i2c,GT9147_ADD,GT_GSTID_REG,2);
    ev_dri_i2c_read(vals->i2c,GT9147_ADD,dat,1);

    if((dat[0]&0X80) == 0)
    {
        return 1;  
    }

    arg->out->tick  = ev_get_tick();
    if((dat[0]&0X10) == 0)
    {
         arg->out->state = 0;
    }
    else
    {

        ev_dri_i2c_write(vals->i2c,GT9147_ADD,GT_TP1_REG,2);
        ev_dri_i2c_read(vals->i2c,GT9147_ADD,dat,4);

        arg->out->state = 1;
        arg->out->x = ((uint16_t)dat[1]<<8)|dat[0];
        arg->out->y = ((uint16_t)dat[3]<<8)|dat[2];
    }

    dat[0] = GT_GSTID_REG[0];
    dat[1] = GT_GSTID_REG[1];
    dat[2] = 0x00;
    ev_dri_i2c_write(vals->i2c,GT9147_ADD,dat,3);
    return 0;
}




static const edev_obj_fun_t EV_TYPE_LIST(ev_tp_gt9147_type)[] ={
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,HELP),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,LINK),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,POWER),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,SUPPORT),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,INIT),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,TP_IC_GET),
};
uint8_t ev_tp_gt9147_type_vals_create(ev_obj_t *obj)
{
    obj->vals = ev_malloc(sizeof(ev_tp_gt9147_val_t));
    if(obj->vals)
    {
        ((ev_tp_gt9147_val_t *)obj->vals)->reset = 0;
        return 0;
    }
    else
    {
        return 1;
    }
}
//自变量释放方法
void ev_tp_gt9147_type_vals_free(ev_obj_t *obj)
{
    if(obj->vals)
    {
        ev_free(obj->vals);
    }
}

const ev_type_t ev_tp_gt9147_type = {
    .name = "ev_tp_gt9147_type",
    .vals_create = ev_tp_gt9147_type_vals_create,
    .vals_free = ev_tp_gt9147_type_vals_free,

    .total = EV_TYPE_TOTAL(ev_tp_gt9147_type),
    .list  = EV_TYPE_LIST(ev_tp_gt9147_type),
};



