#ifndef DVC_REMOTE_H
#define DVC_REMOTE_H

#include "main.h"
#include "drv_usart.h"


#define SBUS_UART huart3

//结构体定义
typedef struct{
    int16_t X_L;
    int16_t Y_L;
    int16_t X_R;
    int16_t Y_R;
    int16_t key_a;
    int16_t key_b;
    int16_t key_c;
    int16_t key_d;
    int16_t adc_a;
    int16_t adc_b;
}remote_t;
extern uint8_t Rx_buf[64];
//函数定义

void Remote_callback(uint8_t *data, uint16_t size);
#endif //DVC_REMOTE_H