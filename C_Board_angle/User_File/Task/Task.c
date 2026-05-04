#include "Task.h"

#include "drv_can.h"
#include "drv_tim.h"
#include "stm32f4xx_hal.h"
#include "drv_usart.h"
#include "dvc_dji_motor.h"
#include "dvc_vofa.h"
#include "drv_tim.h"
#include "dvc_remote.h"

DJ_Motor_t DJ_Motor3508[2];
DJ_Motor_t DJ_Motor2006[2];


/* 毫秒定时器 */
void MM_TIM_Callback(void)
{
    static uint16_t count;
    /***********0.1秒计时器***********/
    if (count++ > 100)
    {
        /***********程序运行指示灯************/
        HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);

        count = 0;
    }
}
/*****任务初始化******/
void Task_Init(void)
{
    /*********开启定时器*********/
    AttachInterrupt_TIM(&htim7,MM_TIM_Callback);
    HAL_TIM_Base_Start_IT(&htim7);
    /*********开启VOFA*********/
    AttachInterrupt_UART_DMA(&huart1,DataBuff,200,Vofa_Callback);

    /*********开启CAN**********/
    AttachInterrupt_CAN(&hcan1, DJ_CAN_Callback);

    DJ_Init(&DJ_Motor3508[0], 3, M3508, PID_METHOD);

    // DJ_Init(&DJ_Motor2006[0], 5, M2006, PID_METHOD);

   // DJ_SetAngle(&DJ_Motor2006[0], 180.0f, 1000.0f);

    DJ_SetAngle(&DJ_Motor3508[0], 360.0f, 1000.0f);
    //DJ_SetAngle(&DJ_Motor2006[0], 360.0f, 1000.0f);

    //DJ_SetSpeed(&DJ_Motor3508[0], 800.0f);

    //DJ_SetSpeed(&DJ_Motor2006[0], 800.0f);


    // /*********遥控测试**********/
    // AttachInterrupt_UART_DMA(&huart3,Rx_buf,64,Remote_callback);
}

/*******任务执行循环*********/
void Task_loop(void)
{
    /********大疆电机运行********/
    uart_pid_to_pid_update();
//这里会覆盖掉在DJ_Init里面通过PID_Init设置的PID_Speed
    DJ_MotorRun();
    /********VOFA绘图**********/

    //justfloat_displayspeeddata(DJ_Motor3508[0].PID_Speed.Kp, DJ_Motor3508[0].PID_Speed.Ki, DJ_Motor3508[0].PID_Speed.Kd, DJ_Motor3508[0].setSpeed, DJ_Motor3508[0].speed);
    //位置环调试反馈
    //justfloat_displayangledata(DJ_Motor3508[0].setAngle,DJ_Motor3508[0].angle,DJ_Motor3508[0].total_angle,DJ_Motor3508[0].PID_SpeedOfAngle.out,DJ_Motor3508[0].PID_Angle.Kp,DJ_Motor3508[0].PID_Angle.Ki,DJ_Motor3508[0].PID_Angle.Kd);

    //justfloat_displayangledata(DJ_Motor2006[0].setAngle,DJ_Motor2006[0].angle,DJ_Motor2006[0].total_angle,DJ_Motor2006[0].PID_SpeedOfAngle.out,DJ_Motor2006[0].PID_Angle.Kp,DJ_Motor2006[0].PID_Angle.Ki,DJ_Motor2006[0].PID_Angle.Kd);

    //justfloat_displayangledata(DJ_Motor2006[0].setAngle,((DJ_Motor2006[0].angle)/8192.0f)*360.0f,DJ_Motor2006[0].total_angle,DJ_Motor2006[0].PID_SpeedOfAngle.out,DJ_Motor2006[0].PID_Angle.Kp,DJ_Motor2006[0].PID_Angle.Ki,DJ_Motor2006[0].PID_Angle.Kd);
    //cplt:total_angle,PID_SpeedOfAngle.out,PID_Angle.Kp,PID_Angle.Ki,PID_Angle.Kd,angle

    justfloat_displayangledata(DJ_Motor3508[0].setAngle,((DJ_Motor3508[0].angle)/8192.0f)*360.0f,DJ_Motor3508[0].total_angle,DJ_Motor3508[0].PID_SpeedOfAngle.out,DJ_Motor3508[0].PID_Angle.Kp,DJ_Motor3508[0].PID_Angle.Ki,DJ_Motor3508[0].PID_Angle.Kd);

}