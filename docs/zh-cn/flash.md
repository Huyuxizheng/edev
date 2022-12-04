# flash

## w25qxx

```c

//定义
const ev_obj_t  flash_dev = 
ev_obj_forge(
	ev_w25q32_spi_m,
	.spi = ev_obj_forge_p(
		ev_spi_m,
        .handle = &hspi1,
		.write = spi_write,
        .read = spi_read,
	),
	.cs_io = ev_obj_forge_p(
			ev_gpio_m, 
			group:GPIOA,
			pin:GPIO_PIN_4,
			set:GPIO_Write,
			get:GPIO_Read,
  ),
);

{
    
    float dat[256] = {0};

    //初始化
    ev_do(flash_dev,INIT);

    //擦除
    ev_do(flash_dev,FLASH_ERASE,0x0001000,1);

    //写入
    ev_do(flash_dev,FLASH_WRITE,0x0001000,dat,256);

    //读取
    ev_do(flash_dev,FLASH_READ,0x0001000,dat,256);

}
```
