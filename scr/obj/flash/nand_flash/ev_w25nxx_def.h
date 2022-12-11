#ifndef __EDEV_W25NXX_DEF_H__
#define __EDEV_W25NXX_DEF_H__

//读设备ID
#define CMD_DEVICE_ID           0x9F    //dummy8bit - id

//写使能失能
#define CMD_WRITE_ENABLE        0x06   
#define CMD_WRITE_DISABLE       0x04


//擦除
#define CMD_BLOCK_ERASE         0xd8    //dummy8bit - addr24bit



//读状态寄存器3，最低位为忙标志位
#define CMD_READ_STATUS_R1      0x05a0    //data
#define CMD_READ_STATUS_R2      0x05b0    //data
#define CMD_READ_STATUS_R3      0x05c0    //data
#define CMD_WRITE_STATUS_R1     0x01a0    //data
#define CMD_WRITE_STATUS_R2     0x01b0    //data
#define CMD_WRITE_STATUS_R3     0x01c0    //data


//普通spi模式读写操作
//busy-CMD_READ_LOAD-busy-CMD_FAST_READ
#define CMD_READ_PAGE           0x13    //addr24bit
#define CMD_READ_DATA           0x03    //cache addr16bit - dummy8bit - data
#define CMD_FAST_READ           0x0b    //cache addr16bit - dummy8bit - data

//busy-WRITE_ENABLE-LOAD_PROGRAM-busy-WRITE_ENABLE-PROGRAM_EXECUTE-busy-CMD_READ_STATUS_R3(ECC)-CMD_READ_LOAD-busy-CMD_FAST_READ(验证拓展部分信息)
#define CMD_LOAD_PROGRAM        0x02    //cache addr16bit - data (reset cache)
#define CMD_RANDOM_LOAD_PROGRAM 0x84    //cache addr16bit - data
#define CMD_PROGRAM_EXECUTE     0x10    //addr24bit



#endif