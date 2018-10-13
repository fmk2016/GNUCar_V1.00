#ifndef __PID_H__
#define __PID_H__
#include "include.h"
#include "common.h"

#define KP 0
#define KI 1
#define KD 2
#define KT 3

typedef struct PID
{
	long SumError;	//����ۼ�	
	int32 LastError;	//Error[-1]
	int32 PrevError;	//Error[-2]	
	int32 LastSpeed;	//Speed[-1]
} PID;

extern PID S_D5_PID, MOTOR_PID;	//�������͵����PID�����ṹ��

//λ��ʽPID������ʼ��
void PlacePID_Init(PID *sptr);

//����ʽPID������ʼ��
void IncPID_Init(PID *sptr);

//λ��ʽPID�������
int32 PlacePID_Control(PID *sprt, int32 NowPiont, int32 SetPoint);

//����ʽ����PID����
int32 PID_Cascade(PID *sprt, int32 NowPiont, int32 SetPoint);

//����ʽPID����
int32 PID_Realize(PID *sptr, int32 ActualSpeed, int32 SetSpeed);

#endif
