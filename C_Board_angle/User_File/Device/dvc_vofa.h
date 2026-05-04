
#ifndef DVC_VOFA_H
#define DVC_VOFA_H


#include "main.h"
#include "drv_usart.h"
#include "dvc_dji_motor.h"
#include <stdlib.h>
//FireWater  0
//JustFloat  1
#define VOFA_DATA_FORMAT 1
//调试模式 1
//不调试模式 0
#define debugmode 1

#define commandlength 200
#define framehead '='
#define frametail '!'

extern uint8_t DataBuff[commandlength];//指令内容

typedef struct{
    float speed_kp;
    float speed_ki;
    float speed_kd;
    float position_kp;
    float position_ki;
    float position_kd;
    float speed_target;

    float angle_target;//zhb写的
}pid_para_t;


void uart_pid_to_pid_update(void);
float Get_Data(void);
void USART_PID_Adjust(uint8_t Motor_n);
void Vofa_Callback(uint8_t *data, uint16_t size);

void justfloat_displayangledata(float position_target,float position_actual,float position_out,float speed_out,float angle_pid_kp,float angle_pid_ki,float angle_pid_kd);
void Float_to_Byte(float f,unsigned char byte[]);
void JustFloat_test(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void justfloat_displayspeeddata(float speed_pid_kp,float speed_pid_ki,float speed_pid_kd,float speed_target,float speed_actual);

#endif //DVC_VOFA_H