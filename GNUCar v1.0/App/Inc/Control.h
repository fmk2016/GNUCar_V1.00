#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "common.h"
#include "include.h"

//定义电机端口		//PTA6	PTA7
#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH0
#define MOTOR2_PWM  FTM_CH1
#define MOTOR3_PWM  FTM_CH2
#define MOTOR4_PWM  FTM_CH3
#define MOTOR_HZ    (10*1000)	//滑行模式下，频率应该是 30~100。
								//常规模式下，频率应该是 20k 左右
extern int32 MOTOR_Duty;
extern int32 MOTOR_Speed;
extern int32 RC_Get;
extern uchar Run_Flag;
extern uchar Game_End;
extern uchar Stop_Flag;
extern uchar BangBang_Flag;

extern char Set;


//定义舵机端口		//PTE5		新板子使用PTD0！！！！！！
#define S_D5_FTM FTM1 
#define S_D5_CH  FTM_CH0
#define S_D5_HZ  (100)
#define S_D5_MID 8610	//  舵机中值  4480

extern uint8   Point_Mid;//目标点横坐标


extern int32 Pulses_Count;//正交解码脉冲计数，必须为 int32 ！！！


/*********** 函数声明 ************/
void speed_measure();		//电机速度测量
void Start_Control(void);	//起跑线检测与停车控制
void MOTOR_Control(void);	//增量式PID调控电机速度
int32 range_protect(int32 duty, int32 min, int32 max); //限幅保护

#endif