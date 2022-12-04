# 霍尔角度传感器

## as5600 

```c

//定义
const ev_obj_t  ang_dev = 
ev_obj_forge(
	ev_as5600_m,
	.i2c = ev_obj_forge_p(
		ev_i2c_imit_m,
		.sda = ev_obj_forge_p(
			ev_gpio_m, 
			group:GPIOB,
			pin:GPIO_PIN_12,
			set:GPIO_Write,
			get:GPIO_Read,
		),
		.scl = ev_obj_forge_p(
			ev_gpio_m, 
			group:GPIOB,
			pin:GPIO_PIN_13,
			set:GPIO_Write,
			get:GPIO_Read,
		),
	),
);

{
    
    float ang = 0;

    //初始化
    ev_do(ang_dev,INIT);
    //获得角度值
    ev_do(ang_dev,HALL_ANG_GET,&ang)

}

```