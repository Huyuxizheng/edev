
#include <stdint.h>
#include "edev_config.h"

#ifdef EV_DEFAULT_DELAY_EN

#define CLK_MHZ     EV_DELAY_CLK_MHZ //主频 兆HZ 不足1M写1M
#define AUX_VAR     EV_DELAY_AUX_VAR//修正系数 一般不调

#define ASM_NUM     EV_DELAY_ASM_NUM //汇编所占周期O3优化,直接查看输出汇编代码确定

char nil = 0;//防止被优化

void ev_default_delay_ns(uint32_t ns)
{
    uint32_t ns_temp = ns * ((CLK_MHZ+ASM_NUM-1)/ASM_NUM * AUX_VAR )/1000;
    while(ns_temp > 0)
    {
        nil--;
        ns_temp--;
    }
}

void ev_default_delay_us(uint32_t us)
{

    uint32_t us_temp = us * ((CLK_MHZ+ASM_NUM-1)/ASM_NUM * AUX_VAR);
    while(us_temp > 0)
    {
        nil--;
        us_temp--;
    }

}

void ev_default_delay_ms(uint32_t ms)
{
    while(ms > 0)
    {
        ev_default_delay_us(999);
        ev_default_delay_ns(999);
        ms--;
    }
}

#endif
