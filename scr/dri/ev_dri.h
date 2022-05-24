#ifndef __EDEV_DRI_H__
#define __EDEV_DRI_H__

typedef const void * ev_drive_s;

#define EV_DRI_E(DRI) EV_DRI_##DRI##_E
#define EV_DRI_S(DRI) const EV_DRI_##DRI##_S
  

#define ev_drive_forge(DRI, ...)  &(const EV_DRI_S(DRI)[]){{__VA_ARGS__}}

enum{
    EV_DRI_E(BASE) = 1,
    EV_DRI_E(GPIO),
    EV_DRI_E(SPI),
    EV_DRI_E(IIC),
};

typedef uint16_t ev_dri_e;

typedef struct{
    ev_dri_e    e;//枚举标识符
    ev_drive_s  p;
}ev_dri_t;

//判断类型-错误返回1
#define ev_dri_e_check(DRI_E,dri) \
((dri)->e != EV_DRI_E(DRI_E))


typedef struct{
    uint8_t   no_arg;
}EV_DRI_S(BASE);

typedef struct{
    //设置电平
    void       (*set)(uint8_t val);
    //反转电平
    void       (*togle)(void);
}EV_DRI_S(GPIO);

typedef struct{
    uint8_t   no_arg;
}EV_DRI_S(SPI);


#endif
