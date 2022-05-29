#include "./dev/tp/ev_tp.h"
#include "./dev/tp/gt9147/ev_tp_gt9147.h"
#include "edev_config.h"
#include "./core/ev_obj_list.h"

#define GT_CMD_WR 		0X28     	//写命令
#define GT_CMD_RD 		0X29		//读命令


//GT9147 部分寄存器定义 
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校验和寄存器
#define GT_PID_REG 		0X8140   	//GT9147产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址  


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



    return 0;
}
EV_TYPE_FUN_DEF(ev_tp_gt9147_type,SUPPORT)
{
    EV_TYPE_FUN_GET_ARG(SUPPORT);

    ev_tp_gt9147_val_t *vals = self->vals;


    if(arg->obj->type == &ev_tp_type)
    {
            return 1;
    }


    return 0;
}
EV_TYPE_FUN_DEF(ev_tp_gt9147_type,TP_IC_GET)
{
    EV_TYPE_FUN_GET_ARG(TP_GET);

    ev_tp_gt9147_val_t *vals = self->vals;



    return 0;
}




static const edev_obj_fun_t EV_TYPE_LIST(ev_tp_gt9147_type)[] ={
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,HELP),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,LINK),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,POWER),
    EV_TYPE_LIST_ADD_FUN(ev_tp_gt9147_type,SUPPORT),
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



