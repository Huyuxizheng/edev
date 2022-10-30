#ifndef __EDEV_CONFIG_H__
#define __EDEV_CONFIG_H__

#include <stdlib.h>
#define ev_malloc(size) malloc(size)
#define ev_free(p)      free(p)  

//递归互斥锁
//#define EV_CONFIG_OS_LOCK_EN

#ifdef EV_CONFIG_OS_LOCK_EN
#define ev_os_lock_create()           malloc(1)
#define ev_os_lock_free(lock_p)       free(lock_p)  
#define ev_os_lock(lock_p)    
#define ev_os_unlock(lock_p)
#endif


//默认延时函数配置 
#define EV_DELAY_CLK_MHZ    48 //主频 兆HZ 不足1M写1M
#define EV_DELAY_AUX_VAR    1//修正系数 一般不调
#define EV_DELAY_ASM_NUM    10 //汇编所占周期O3优化,直接查看输出汇编代码确定

extern void ev_default_delay_ns(uint32_t ns);
extern void ev_default_delay_us(uint32_t us);
extern void ev_default_delay_ms(uint32_t ms);


#define ev_sleep_ns(ns)     
#define ev_sleep_us(us)    
#define ev_sleep(ms)        
#define ev_get_tick()       0

#define ev_error(...)           
#define ev_warning(...)         
#define ev_info(...)            

#endif
