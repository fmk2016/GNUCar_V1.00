#include "PID.h"

PID S_D5_PID, MOTOR_PID;	//�������͵����PID�����ṹ��
int32 S_D5[10][4] = {{37, 0, 15, 16},
                     {20, 1,  0, 19}, 
                     {24, 2, 15, 28},
                     {24, 3, 22, 14}, 
                     {20, 4, 25, 14}, 
                     {24, 5, 24, 13}, 
                     {26, 6, 18 ,13}, 
                     {25, 7, 27, 14},
                     {29, 8, 35, 13}};	//���PID
  
                    /*{ 20, 1, 0, 19},
                      {24, 2, 15, 28},
                      {22, 3, 24, 14},
                      {23, 4, 29, 15},
                      {25, 5, 21, 14},
                      {26, 6, 18, 14},
                      {             },
                      {28, 7, 32, 14}��
                      {27, 8, 35, 12};*/
					/* PID �� I ��û��ʹ�ã�ֻ�� PD6�˴� I ����Ϊ�ٶ�ģʽ�ı�ţ���PID��Ӱ�� */					

//λ��ʽPID������ʼ��
//float   MOTOR[3] = {4, 0.7, 0};
float   MOTOR[3] = {5, 0.4, 0};	//���PID
void PlacePID_Init(PID *sptr)
{
	sptr->SumError = 0;
	sptr->LastError = 0;	//Error[-1]
	sptr->PrevError = 0;	//Error[-2]
}

//����ʽPID������ʼ��
void IncPID_Init(PID *sptr)
{
	sptr->SumError = 0;
	sptr->LastError = 0;	//Error[-1]
	sptr->PrevError = 0;	//Error[-2]	
	sptr->LastSpeed = 0;
}

//λ��ʽPID�������
int32 PlacePID_Control(PID *sprt, int32 NowPiont, int32 SetPoint)
{
	//����Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
	int32 iError,	//��ǰ���
	      Actual;	//���ó���ʵ�����ֵ
	float	Kp;		//��̬P

	
	iError = SetPoint - NowPiont;	//���㵱ǰ���
        
	Kp = 1.0 * (iError*iError) / S_D5[Set][KT] + S_D5[Set][KP];	//Pֵ���ֵ�ɶ��κ�����ϵ	
	Actual = Kp * iError + S_D5[Set][KD] * (iError - sprt->LastError);//ֻ��PD
        
	//Actual = 9 * iError;
	sprt->LastError = iError;		//�����ϴ����
	
        /*if (Actual)
        {
            Actual = Actual * 90 / 100;
        } */
	
	return  S_D5_MID-Actual;
        //return Actual;
}

//����ʽ����PID����
int32 PID_Cascade(PID *sptr, int32 ActualSpeed, int32 SetSpeed)
{
	//��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
	register int32 iError,	    //��ǰ���
					Increase;	//���ó���ʵ������
	
	iError = SetSpeed - ActualSpeed;//���㵱ǰ���
	
	Increase = - MOTOR[KP] * (ActualSpeed - sptr->LastSpeed)	//���ٶ�
			   + MOTOR[KI] * iError
			   + MOTOR[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	//����ǰ�����
	sptr->LastError = iError;		  	//�����ϴ����
	sptr->LastSpeed = ActualSpeed;		//�����ϴ��ٶ�
	
	if (iError < -100)
	{
		Increase -= 400;
	}
	else if (iError < -80)
	{
		Increase -= 300;
	}
	else if (iError < -50)
	{
		Increase -= 250;
	}
	else if (iError < -30)
	{
		Increase -= 200;
	}
        
/*        if (iError < -100)
	{
		Increase -= 200;
	}
	else if (iError < -80)
	{
		Increase -= 150;
	}
	else if (iError < -50)
	{
		Increase -= 125;
	}
        else if (iError < -30)
        {
                Increase -= 100;
        }*/
	
	return Increase;
        
}	

//����ʽPID�������
int32 PID_Realize(PID *sptr, int32 ActualSpeed, int32 SetSpeed)
{
	//��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
	register int32 iError,	    //��ǰ���
					Increase;	//���ó���ʵ������
	
	iError = SetSpeed - ActualSpeed;//���㵱ǰ���
	
	Increase = MOTOR[KP] * (iError - sptr->LastError)
			 + MOTOR[KI] * iError
			 + MOTOR[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	//����ǰ�����
	sptr->LastError = iError;		  	//�����ϴ����
	
	if (iError < -70)
	{
		BangBang_Flag = 1;
		Increase -= 80;
	}
	else if (iError < -50)
	{
		BangBang_Flag = 1;
		Increase -= 50;
	}
	else if (iError < -30)
	{
		BangBang_Flag = 1;
		Increase -= 20;
	}

	if ((iError > 50) && (BangBang_Flag == 1))
	{
		BangBang_Flag = 0;
		Increase +=  170;
	}
	else if (iError > 50)
	{
		Increase += 120;
	}
	
	return Increase;
}



