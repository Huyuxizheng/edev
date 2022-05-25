#ifndef __EDEV_CONFIG_H__
#define __EDEV_CONFIG_H__

#include <stdlib.h>
#define ev_malloc(size) malloc(size)
#define ev_free(p)      free(p)  


#define ev_error(...)  
#define ev_warning(...)        
#define ev_info(...) 

#endif
