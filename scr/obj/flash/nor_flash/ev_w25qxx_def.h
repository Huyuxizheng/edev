#ifndef __EDEV_W25QXX_DEF_H__
#define __EDEV_W25QXX_DEF_H__

//读设备ID
#define CMD_DEVICE_ID           0x90    //dummy8bit - dummy8bit - 0x00 - id

//写使能失能
#define CMD_WRITE_ENABLE        0x06   
#define CMD_WRITE_DISABLE       0x04


//擦除
#define CMD_SECTOR_ERASE        0x20    //addr24bit
#define CMD_ERASE_8_SECTOR      0x52    //addr24bit
#define CMD_ERASE_16_SECTOR     0xd8    //addr24bit
#define CMD_CHIP_ERASE          0x60

#define CMD_SECTOR_ERASE_4A     0x21    //addr32bit
#define CMD_ERASE_16_SECTOR_4A  0xdc    //addr32bit


//读状态寄存器1，最低位为忙标志位
#define CMD_READ_STATUS_R1      0x05    //data

//普通spi模式读写操作
#define CMD_READ_DATA           0x03    //addr24bit - data
#define CMD_FAST_READ           0x0b    //addr24bit - dummy8bit - data
#define CMD_PAGE_PROGRAM        0x02    //addr24bit - data

#define CMD_READ_DATA_4A        0x13    //addr32bit - data
#define CMD_FAST_READ_4A        0x0c    //addr32bit - dummy8bit - data
#define CMD_PAGE_PROGRAM_4A     0X12    //addr32bit - data


#endif