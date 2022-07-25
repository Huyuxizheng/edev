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


#define ev_sleep(ms)        
#define ev_get_tick()       0

#define ev_error(...)           
#define ev_warning(...)         
#define ev_info(...)            

#endif
