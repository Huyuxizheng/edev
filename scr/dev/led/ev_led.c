#include "./dev/led/ev_led.h"
#include "edev_config.h"

typedef struct{
    EV_DRI_S(GPIO) *gpio;
    uint8_t         en_val;
}ev_led_vals_s;

EV_TYPE_FUN_DEF(ev_led_type,HELP)
{
    EV_TYPE_FUN_GET_ARG(HELP);
/*
    //创建led 的 gpio驱动
    ev_drive_s *led_gpio = ev_drive_forge(GPIO, 
                                            .group = GPIOA,
                                            .pin   = PIN_1,
                                            .set   = gpio_set,
                                            .togle = gpio_togle
                                        );
    //创建LED设备
    ev_obj_s *led_dev = ev_obj_create(ev_led_type);

    //LED设备增加gpio驱动
    ev_obj_fun(led_dev, LINK, led_gpio);

    //设置LED引脚高电平为点亮
    ev_obj_fun(led_dev, LED_SET_EN_VAL, 1);  

    //设置LED
    ev_obj_fun(led_dev, LED_SET, 1);  

    //反转LED
    ev_obj_fun(led_dev, LED_TOGLE, 0);                                       
*/

    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,LINK)
{
    EV_TYPE_FUN_GET_ARG(LINK);

    ev_led_vals_s *vals = self->vals;

    if(ev_dri_e_check(GPIO,arg->drive) == 0)
    {
        vals->gpio = arg->drive->p;
        return 0;
    }

    return 1;
}

EV_TYPE_FUN_DEF(ev_led_type,LED_SET)
{
    EV_TYPE_FUN_GET_ARG(LED_SET);
    ev_led_vals_s *vals = self->vals;
    if(vals->gpio)
    {
        ev_dri_gpio_set(vals->gpio,vals->en_val);
    }
    return 0;
}


EV_TYPE_FUN_DEF(ev_led_type,LED_TOGLE)
{
    EV_TYPE_FUN_GET_ARG(LED_TOGLE);
    ev_led_vals_s *vals = self->vals;
    if(vals->gpio)
    {
        ev_dri_gpio_togle(vals->gpio);
    }

    return 0;
}
EV_TYPE_FUN_DEF(ev_led_type,LED_SET_EN_VAL)
{
    EV_TYPE_FUN_GET_ARG(LED_SET_EN_VAL);
    ev_led_vals_s *vals = self->vals;

    vals->en_val = arg->en_val;

    return 0;
}

static const edev_obj_fun_t EV_TYPE_LIST(ev_led_type)[] ={
    EV_TYPE_LIST_ADD_FUN(ev_led_type,HELP),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,LINK),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,LED_SET),
    EV_TYPE_LIST_ADD_FUN(ev_led_type,LED_TOGLE),
};
uint8_t ev_led_type_vals_create(ev_obj_s *obj)
{
    obj->vals = ev_malloc(sizeof(ev_led_vals_s));
    if(obj->vals)
    {
        ((ev_led_vals_s *)obj->vals)->en_val = 0;
        return 0;
    }
    else
    {
        return 1;
    }
}
//自变量释放方法
void ev_led_type_vals_free(ev_obj_s *obj)
{
    if(obj->vals)
    {
        ev_free(obj->vals);
    }
}

const ev_type_s ev_led_type = {
    .name = "ev_led_type",
    .vals_create = ev_led_type_vals_create,
    .vals_free = ev_led_type_vals_free,

    .total = EV_TYPE_TOTAL(ev_led_type),
    .list  = EV_TYPE_LIST(ev_led_type),
};


