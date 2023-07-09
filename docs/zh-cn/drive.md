## 外设简介
外设模型是和硬件唯一相关的模型，实现方法提供了两类，一类为通用的实现，需要自行完善，一类是和芯片绑定的实现，可直接调用。
## gpio

## adc

## i2c
i2c设备提供了两种通用模型，用于分别实现模拟i2c和硬件i2c
### 方法列表
#### INIT
* 说明：以默认100KHz初始化I2C
* 无参数
* 返回值：`uint8_t` 0为成功，其他则失败
``` c
extern const ev_obj_t i2c_dev;
void test(void)
{
    //初始化I2C设备100KHz
    ev_do(i2c_dev,INIT);
}
```

#### I2C_INIT
* 说明：初始化i2c并指定最大频率（实际频率小于等于设置的频率）
* 参数1：`uint32_t max_khz` 最大频率单位KHz
* 返回值：0为成功，其他则失败
``` c
extern const ev_obj_t i2c_dev;
void test(void)
{
    //初始化I2C设备400KHz
    ev_do(i2c_dev,I2C_INIT,400);
}
```

#### I2C_WRITE
* 说明：向i2c写入数据
* 参数1：`uint8_t addr` 高7位为i2c设备地址，最低位任意
* 参数2：`const uint8_t *data` 要传输的数据，数组
* 参数3：`uint32_t size` 数据长度
* 参数4：`uint8_t no_stop` 为真则不发送结束信号
* 返回值：`uint8_t`0为成功，其他则失败
```c
extern const ev_obj_t i2c_dev;
void test(void)
{
    #define ADDR (0x0c<<1)
    float dat[256] = {0};

    //初始化I2C设备400KHz
    ev_do(i2c_dev,I2C_INIT,400);

    //向I2C写入256个数据
    ev_do(i2c_dev,I2C_WRITE,ADDR,dat,256);

    //向I2C写入256个数据，不发送结束信号
    ev_do(i2c_dev,I2C_WRITE,ADDR,dat,256,.no_stop = 1);
}
```

#### I2C_READ
* 说明：从i2c读出数据
* 参数1：`uint8_t addr` 高7位为i2c设备地址，最低位任意
* 参数2：`uint8_t *data` 要接收数据的数组
* 参数3：`uint32_t size` 数据长度
* 参数4：`uint8_t no_stop` 为真则不发送结束信号
* 返回值：`uint8_t`0为成功，其他则失败
```c
extern const ev_obj_t i2c_dev;
void test(void)
{
    #define ADDR (0x0c<<1)
    float dat[256] = {0};

    //初始化I2C设备400KHz
    ev_do(i2c_dev,I2C_INIT,400);

    //从i2c读出256个数据
    ev_do(i2c_dev,I2C_READ,ADDR,dat,256);

    //从i2c读出256个数据，不发送结束信号
    ev_do(i2c_dev,I2C_READ,ADDR,dat,256,.no_stop = 1);
}
```

#### I2C_MEM_WRITE
* 说明：向i2c写入寄存器数据
* 参数1：`uint8_t addr` 高7位为i2c设备地址，最低位任意
* 参数2：`uint16_t mem_addr` 寄存器地址
* 参数3：`uint32_t mem_addr_size` 寄存器地址长度
* 参数4：`uint8_t *data` 要传输的数据，数组
* 参数5：`uint32_t size` 数据长度
* 返回值：`uint8_t`0为成功，其他则失败
```c
extern const ev_obj_t i2c_dev;
void test(void)
{
    #define ADDR        (0x0c<<1)
    #define REG_ADDR    0x01
    #define REG_ADDR2   0x0108
    float dat[256] = {0};

    //初始化I2C设备400KHz
    ev_do(i2c_dev,I2C_INIT,400);

    //从i2c写入256个数据到寄存器0x01
    ev_do(i2c_dev,I2C_MEM_WRITE,ADDR,REG_ADDR,1,dat,256);

    //从i2c写入256个数据到寄存器0x0108
    ev_do(i2c_dev,I2C_MEM_WRITE,ADDR,REG_ADDR2,2,dat,256);
}
```

####  I2C_MEM_READ
* 说明：从i2c读出寄存器数据
* 参数1：`uint8_t addr` 高7位为i2c设备地址，最低位任意
* 参数2：`uint16_t mem_addr` 寄存器地址
* 参数3：`uint32_t mem_addr_size` 寄存器地址长度
* 参数4：`uint8_t *data` 要接收数据的数组
* 参数5：`uint32_t size` 数据长度
* 返回值：`uint8_t`0为成功，其他则失败
```c
extern const ev_obj_t i2c_dev;
void test(void)
{
    #define ADDR        (0x0c<<1)
    #define REG_ADDR    0x01
    #define REG_ADDR2   0x0108
    float dat[256] = {0};

    //初始化I2C设备400KHz
    ev_do(i2c_dev,I2C_INIT,400);

    //从i2c寄存器0x01读出256个数据
    ev_do(i2c_dev,I2C_MEM_READ,ADDR,REG_ADDR,1,dat,256);

    //从i2c寄存器0x0108读出256个数据
    ev_do(i2c_dev,I2C_MEM_READ,ADDR,REG_ADDR2,2,dat,256);
}
```

### 模拟i2c模型
#### ev_i2c_imit_m
* 模型名`ev_i2c_imit_m`
* 属性
    * `const ev_obj_t* sda` sda IO口的GPIO对象
    * `const ev_obj_t* scl` scl IO口的GPIO对象

#### 声明示例
``` c
//定义模拟I2C
const ev_obj_t i2c_dev = ev_forge(//制造对象
	ev_i2c_imit_m,//模拟I2C模型
	.sda = ev_forge_p(//制造匿名对象
		ev_gpio_m,//GPIO模型
		.group=GPIOA,
		.pin  =GPIO_PIN_4,
		.set  =GPIO_Write,
		.get  =GPIO_Read,
	),
	.scl = ev_forge_p(//制造匿名对象
        ev_gpio_m,//GPIO模型
		.group=GPIOA,
		.pin  =GPIO_PIN_4,
		.set  =GPIO_Write,
		.get  =GPIO_Read,
  ),
);
```

### 硬件i2c 模型
#### ev_i2c_m
* 模型名`ev_i2c_m`
* 属性
    * `void* handle` 可选的 I2C句柄
    * `uint8_t (*init)(void* handle,uint32_t max_khz)` 
    初始化函数指针
    * `uint8_t (*write)(void* handle,uint8_t addr,const uint8_t *dat,uint16_t len,uint8_t no_stop)`
    写入数据函数指针
    * `uint8_t (*read)(void* handle,uint8_t addr,uint8_t *dat,uint16_t len,uint8_t no_stop)`
    读出数据函数指针
    * `void (*uninit)(void* handle)`
    反初始化函数指针

需要实现四个函数 `init` `write` `read` `uninit`
``` c
uint8_t i2c_init(void* handle,uint32_t max_khz)
{//handle为定义时设置的句柄
    //初始化为小于等于max_khz频率的I2C
}
uint8_t i2c_write(void* handle,uint8_t addr,const uint8_t *dat,uint16_t len,uint8_t no_stop)
{
    if(no_stop)
    {
        //向addr地址的I2C设备写入数据dat长度len，不发送结束信号
    }
    else
    {
        //向addr地址的I2C设备写入数据dat长度len，发送结束信号
    }
}
uint8_t i2c_read(void* handle,uint8_t addr,uint8_t *dat,uint16_t len,uint8_t no_stop)
{
    if(no_stop)
    {
        //从addr地址的I2C设备读出数据到dat长度len，不发送结束信号
    }
    else
    {
        //从addr地址的I2C设备读出数据到dat长度len，发送结束信号
    }
}
void i2c_uninit(void* handle)
{
    //i2c设备反初始化
}
```
#### 声明示例
``` c
extern void* i2c_h;
uint8_t i2c_init(void* handle,uint32_t max_khz);
uint8_t i2c_write(void* handle,uint8_t addr,const uint8_t *dat,uint16_t len,uint8_t no_stop);
int8_t  i2c_read(void* handle,uint8_t addr,uint8_t *dat,uint16_t len,uint8_t no_stop);
void    i2c_uninit(void* handle);
//定义硬件I2C
const ev_obj_t i2c_dev = ev_forge(//制造对象
	ev_i2c_m,//硬件I2C模型
    .handle = i2c_h,//i2c设备句柄调用init、write、read、uninit时传入，可不设置
    .init   = i2c_init,
    .write  = i2c_write,
    .read   = i2c_read,
    .uninit = i2c_uninit,
);
```
## spi