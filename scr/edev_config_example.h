#ifndef __EDEV_CONFIG_H__
#define __EDEV_CONFIG_H__

#include <stdlib.h>

//使用互斥锁 RTOS支持
//#define EV_CONFIG_OS_LOCK_EN

#ifdef EV_CONFIG_OS_LOCK_EN
#define ev_os_lock_create()           malloc(1)
#define ev_os_lock_free(lock_p)       free(lock_p)  
#define ev_os_lock(lock_p)    
#define ev_os_unlock(lock_p)
#endif


//内部默认延时函数配置 ，使用时配置
//#define EV_DEFAULT_DELAY_EN
#ifdef EV_DEFAULT_DELAY_EN
//使用内部延时
#define EV_DELAY_CLK_MHZ    48 //主频 兆HZ 不足1M写1M
#define EV_DELAY_AUX_VAR    1//修正系数 一般不调
#define EV_DELAY_ASM_NUM    10 //汇编所占周期O3优化,直接查看输出汇编代码确定

extern void ev_default_delay_ns(uint32_t ns);
extern void ev_default_delay_us(uint32_t us);
extern void ev_default_delay_ms(uint32_t ms);

#define ev_sleep_ns(ns)     ev_default_delay_ns(ns)
#define ev_sleep_us(us)     ev_default_delay_us(us)
#define ev_sleep(ms)        ev_default_delay_ms(ms)

#else
//不适用内部延时
#define ev_sleep_ns(ns)     
#define ev_sleep_us(us)     
#define ev_sleep(ms)        
#endif


//获得系统运行ms数
#define ev_get_tick()       0 

//打印日志
#define ev_error(...)           
#define ev_warning(...)         
#define ev_info(...)            

#endif
