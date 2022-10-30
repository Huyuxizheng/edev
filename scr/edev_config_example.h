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

/*
默认的延时函数，如果使用需要在ev_delay中配置主频和测试修正系数
extern void ev_default_delay_ns(uint32_t ns);
extern void ev_default_delay_us(uint32_t us);
extern void ev_default_delay_ms(uint32_t ms);
*/

#define ev_sleep_ns(ns)     
#define ev_sleep_us(us)    
#define ev_sleep(ms)        
#define ev_get_tick()       0

#define ev_error(...)           
#define ev_warning(...)         
#define ev_info(...)            

#endif
