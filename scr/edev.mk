EDEV_C_SOURCES =  \
edev/scr/core/ev_core.c\
edev/scr/core/ev_delay.c\
edev/scr/obj/common/ev_adp.c\
edev/scr/obj/common/ev_buff1.c\
edev/scr/obj/common/ev_heap1.c\
edev/scr/obj/drive/ev_adc.c\
edev/scr/obj/drive/ev_gpio.c\
edev/scr/obj/drive/ev_i2c_imit.c\
edev/scr/obj/drive/ev_i2c.c\
edev/scr/obj/drive/ev_spi.c\
edev/scr/obj/flash/nand_flash/ev_w25nxx_ecc_spi.c\
edev/scr/obj/flash/nor_flash/ev_w25q32_spi.c\
edev/scr/obj/flash/nor_flash/ev_w25qxx_spi.c\
edev/scr/obj/flash/ev_flash.c\
edev/scr/obj/hall_ang/as5600/ev_as5600.c\
edev/scr/obj/hall_ang/ev_hall_ang.c\
edev/scr/obj/led/ev_led.c\
edev/scr/obj/tp/gt9147/ev_tp_gt9147.c\
edev/scr/obj/tp/ev_tp.c

EDEV_C_INCLUDES =  \
-Iedev/scr/ \
-Iedev/scr/core\
-Iedev/scr/obj/common\
-Iedev/scr/obj/drive\
-Iedev/scr/obj/flash\
-Iedev/scr/obj/flash/nand_flash\
-Iedev/scr/obj/flash/nor_flash\
-Iedev/scr/obj/hall_ang\
-Iedev/scr/obj/hall_ang/as5600\
-Iedev/scr/obj/led\
-Iedev/scr/obj/tp/gt9147\
-Iedev/scr/obj/tp