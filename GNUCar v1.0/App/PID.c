#include "PID.h"

PID S_D5_PID, MOTOR_PID;	//定义舵机和电机的PID参数结构体
int32 S_D5[10][4] = {{37, 0, 15, 16},
                     {20, 1,  0, 19}, 
                     {24, 2, 15, 28},
                     {24, 3, 22, 14}, 
                     {20, 4, 25, 14}, 
                     {24, 5, 24, 13}, 
                     {26, 6, 18 ,13}, 
                     {25, 7, 27, 14},
                     {29, 8, 35, 13}};	//舵机PID
  
                    /*{ 20, 1, 0, 19},
                      {24, 2, 15, 28},
                      {22, 3, 24, 14},
                      {23, 4, 29, 15},
                      {25, 5, 21, 14},
                      {26, 6, 18, 14},
                      {             },
                      {28, 7, 32, 14}，
                      {27, 8, 35, 12};*/
					/* PID 的 I 项没有使用，只用 PD6此处 I 仅作为速度模式的标号，对PID无影响 */					

//位置式PID参数初始化
//float   MOTOR[3] = {4, 0.7, 0};
float   MOTOR[3] = {5, 0.4, 0};	//电机PID
void PlacePID_Init(PID *sptr)
{
	sptr->SumError = 0;
	sptr->LastError = 0;	//Error[-1]
	sptr->PrevError = 0;	//Error[-2]
}

//增量式PID参数初始化
void IncPID_Init(PID *sptr)
{
	sptr->SumError = 0;
	sptr->LastError = 0;	//Error[-1]
	sptr->PrevError = 0;	//Error[-2]	
	sptr->LastSpeed = 0;
}

//位置式PID舵机控制
int32 PlacePID_Control(PID *sprt, int32 NowPiont, int32 SetPoint)
{
	//定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
	int32 iError,	//当前误差
	      Actual;	//最后得出的实际输出值
	float	Kp;		//动态P

	
	iError = SetPoint - NowPiont;	//计算当前误差
        
	Kp = 1.0 * (iError*iError) / S_D5[Set][KT] + S_D5[Set][KP];	//P值与差值成二次函数关系	
	Actual = Kp * iError + S_D5[Set][KD] * (iError - sprt->LastError);//只用PD
        
	//Actual = 9 * iError;
	sprt->LastError = iError;		//更新上次误差
	
        /*if (Actual)
        {
            Actual = Actual * 90 / 100;
        } */
	
	return  S_D5_MID-Actual;
        //return Actual;
}

//增量式串级PID控制
int32 PID_Cascade(PID *sptr, int32 ActualSpeed, int32 SetSpeed)
{
	//当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
	register int32 iError,	    //当前误差
					Increase;	//最后得出的实际增量
	
	iError = SetSpeed - ActualSpeed;//计算当前误差
	
	Increase = - MOTOR[KP] * (ActualSpeed - sptr->LastSpeed)	//加速度
			   + MOTOR[KI] * iError
			   + MOTOR[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	//更新前次误差
	sptr->LastError = iError;		  	//更新上次误差
	sptr->LastSpeed = ActualSpeed;		//更新上次速度
	
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

//增量式PID电机控制
int32 PID_Realize(PID *sptr, int32 ActualSpeed, int32 SetSpeed)
{
	//当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
	register int32 iError,	    //当前误差
					Increase;	//最后得出的实际增量
	
	iError = SetSpeed - ActualSpeed;//计算当前误差
	
	Increase = MOTOR[KP] * (iError - sptr->LastError)
			 + MOTOR[KI] * iError
			 + MOTOR[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	//更新前次误差
	sptr->LastError = iError;		  	//更新上次误差
	
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



