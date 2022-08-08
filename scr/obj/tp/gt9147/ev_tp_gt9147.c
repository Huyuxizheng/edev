#include "./obj/tp/ev_tp.h"
#include "./obj/tp/gt9147/ev_tp_gt9147.h"
#include "./obj/drive/ev_gpio.h"
#include "./obj/drive/ev_i2c.h"
#include "edev_config.h"

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
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校验和寄存器

#define GT_PID_REG 		0X8140   	//GT9147产品ID寄存器
#define GT_GSTID_REG 	0X814E  	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址




EV_TYPE_FUN_DEF(ev_tp_gt9147_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_gt9147_type,HELP);
/*zhon
                                   
*/

    return 0;
}

EV_TYPE_FUN_DEF(ev_tp_gt9147_type,INIT)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_gt9147_type,INIT);

    uint8_t dat[6] = {0};

    _ev_obj_fun(attr->i2c,INIT);
    _ev_obj_fun(attr->rst_io,GPIO_INIT_OUT);

    _ev_obj_fun(attr->rst_io,GPIO_SET,1);
    ev_sleep(5);
    _ev_obj_fun(attr->rst_io,GPIO_SET,0);
    ev_sleep(1);
    _ev_obj_fun(attr->rst_io,GPIO_SET,1);
    ev_sleep(5);
    _ev_obj_fun(attr->isr_io,GPIO_INIT_ISR);
    ev_sleep(100);


    _ev_obj_fun(attr->i2c,I2C_MEM_READ,GT9147_ADD,GT_PID_REG,2,dat,4);

    if(
        (
            (dat[0] != '9') &&
            (dat[1] != '1') &&
            (dat[2] != '4') &&
            (dat[3] != '7') 
        )
    )
    {
        ev_info("gt9147 read id fail\r\n");
        return 1;
    }

    ev_info("gt9147 id:%s \r\n",id);


    dat[0] = 0x02;
    _ev_obj_fun(attr->i2c,I2C_MEM_WRITE,GT9147_ADD,GT_CTRL_REG,2,dat,1);//软件复位

    _ev_obj_fun(attr->i2c,I2C_MEM_READ,GT9147_ADD,GT_CFGS_REG,2,dat,1);

    if(dat[0]<0X60)//默认版本比较低,需要更新flash配置
    {
        uint8_t buf[2] = {0,1};
        for(int i=2;i<sizeof(GT9147_CFG);i++)buf[0]+=GT9147_CFG[i];
        buf[0]=(~buf[0])+1;

        _ev_obj_fun(attr->i2c,I2C_WRITE,GT9147_ADD,GT9147_CFG,sizeof(GT9147_CFG));//发送寄存器配置

        _ev_obj_fun(attr->i2c,I2C_MEM_WRITE,GT9147_ADD,GT_CHECK_REG,2,buf,2);
    }
    ev_sleep(10);

    dat[0] = 0x00;
    _ev_obj_fun(attr->i2c,I2C_MEM_WRITE,GT9147_ADD,GT_CTRL_REG,2,dat,1);//复位结束

    return 0;
}

EV_TYPE_FUN_DEF(ev_tp_gt9147_type,TP_GET)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_gt9147_type,TP_GET);

    uint8_t dat[6] = {0};
    
    _ev_obj_fun(attr->i2c,I2C_MEM_READ,GT9147_ADD,GT_GSTID_REG,2,dat,1);

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

        _ev_obj_fun(attr->i2c,I2C_MEM_READ,GT9147_ADD,GT_TP1_REG,2,dat,4);

        arg->out->state = 1;
        arg->out->x = ((uint16_t)dat[1]<<8)|dat[0];
        arg->out->y = ((uint16_t)dat[3]<<8)|dat[2];
    }

    dat[0] = 0x00;
    _ev_obj_fun(attr->i2c,I2C_MEM_WRITE,GT9147_ADD,GT_GSTID_REG,2,dat,1);

    return 0;
}

EV_TYPE_FUN_DEF(ev_tp_gt9147_type,UNINIT)
{
    EV_TYPE_FUN_GET_ARG(ev_tp_gt9147_type,UNINIT);

    _ev_objs_fun(attr->i2c,attr->rst_io,attr->isr_io,UNINIT,());


    return 0;
}

EV_TYPE_LIST_DEF(ev_tp_gt9147_type,HELP,INIT,TP_GET,UNINIT);

const ev_type_t ev_tp_gt9147_type = EV_TYPE_DEF(ev_tp_gt9147_type);


