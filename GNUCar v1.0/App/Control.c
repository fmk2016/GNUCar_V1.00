#include "Control.h"
#include "math.h"

uchar   BangBang_Flag = 0;
uchar 	Run_Flag  = 0;
int32   RC_Get = 1500;			//ң������ͨ��ֵ
uchar   Game_End = 1;
uchar   Stop_Flag = 1;
int16   Max_Speed   = 300;
int32   MOTOR_Duty  = 0;
int32   MOTOR_Speed = 0;
int32 Pulses_Count = 0;//���������������������Ϊ int32 ������

char Set = 7;

/******** ������� *********/
void MOTOR_Control(void)
{
	int32 Set_Speed;
	uchar i;          //��������
	uchar Send_Count; //������Ҫ���͵����ݸ���

	if (Run_Flag)
	{
		if (Set == 1)
		{
			Set_Speed = 140;
		}
		else if (Set == 2)
		{
			Set_Speed = 150;
		}
		else if (Set == 3)
		{
			Set_Speed = 160;
		}
		else if (Set == 4)
		{
			Set_Speed = 170;
		}
		else if (Set == 5)
		{
			if (Foresight >= 18)
			{
				Set_Speed = 170;
			}
			else if (Foresight >= 16)
			{
				Set_Speed = 180;
			}
			else if (Foresight >= 14)
			{
				Set_Speed = 190;
			}
			else if (Foresight >= 12)
			{
				Set_Speed = 200;
			}
			else if (Foresight >= 10)
			{
				Set_Speed = 205;
			}
			else if (Foresight >= 8)
			{
				Set_Speed = 210;
			}
			else if (Foresight >= 7)
			{
				Set_Speed = 220;
			}
			else if (Foresight >= 6)
			{
				Set_Speed = 230;
			}
			else if (Foresight >= 5)
			{
				Set_Speed = 240;
			}
			else
			{
				Set_Speed = 255;
			}
		}
		else if (Set == 6)
		{
			if (Foresight >= 18)
			{
				Set_Speed = 175;
			}
			else if (Foresight >= 16)
			{
				Set_Speed = 185;
			}
			else if (Foresight >= 14)
			{
				Set_Speed = 195;
			}
			else if (Foresight >= 12)
			{
				Set_Speed = 205;
			}
			else if (Foresight >= 10)
			{
				Set_Speed = 215;
			}
			else if (Foresight >= 8)
			{
				Set_Speed = 220;
			}
			else if (Foresight >= 7)
			{
				Set_Speed = 230;
			}
			else if (Foresight >= 6)
			{
				Set_Speed = 240;
			}
			else if (Foresight >= 5)
			{
				Set_Speed = 250;
			}
			else
			{
				Set_Speed = 265;
			}
		}
		else if (Set == 7)
		{
			if (Foresight >= 18)
			{
				Set_Speed = 180;
			}
			else if (Foresight >= 16)
			{
				Set_Speed = 210;
			}
			else if (Foresight >= 14)
			{
				Set_Speed = 220;
			}
			else if (Foresight >= 12)
			{
				Set_Speed = 225;
			}
			else if (Foresight >= 10)
			{
				Set_Speed = 235;
			}
			else if (Foresight >= 8)
			{
				Set_Speed = 245;
			}
			else if (Foresight >= 6)
			{
				Set_Speed = 250;
			}
			else if (Foresight >= 5)
			{
				Set_Speed = 255;
			}
			else if (Foresight >= 4)
			{
				Set_Speed = 265;
			}
			else
			{
				Set_Speed = 280;
			}
		}
		else if (Set == 8)
		{
			if (Foresight >= 18)
			{
				Set_Speed = 195;
			}
			else if (Foresight >= 16)
			{
				Set_Speed = 205;
			}
			else if (Foresight >= 14)
			{
				Set_Speed = 220;
			}
			else if (Foresight >= 12)
			{
				Set_Speed = 230;
			}
			else if (Foresight >= 10)
			{
				Set_Speed = 240;
			}
			else if (Foresight >= 8)
			{
				Set_Speed = 250;
			}
			else if (Foresight >= 6)
			{
				Set_Speed = 260;
			}
			else if (Foresight >= 5)
			{
				Set_Speed = 270;
			}
			else if (Foresight >= 4)
			{
				Set_Speed = 280;
			}
			else
			{
				Set_Speed = 290;
			}
		}
		else if (Set == 0)
		{
			if (RC_Get > 1300)
			{
				Set_Speed = 70 + 80 * (RC_Get - 1000) / 1000;
			}
			else
			{
				Set_Speed = 0;
			}
			Set_Speed = range_protect(Set_Speed, 0, 180);
		}
	}
	else
	{
		Set_Speed = 0;
	}
	
		
	MOTOR_Duty += PID_Cascade(&MOTOR_PID, MOTOR_Speed, Set_Speed);//ʹ�ô�������ʽPID���е���
//	MOTOR_Duty = 200;
	
	if ((!Run_Flag || !Set_Speed) && MOTOR_Speed > -10 && MOTOR_Speed < 10)
	{
		MOTOR_Duty = 0;
	}
	if (MOTOR_Duty >= 0)
	{
		MOTOR_Duty = range_protect(MOTOR_Duty, 0, 900);	//�޷�����
					//�����ת
		ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,MOTOR_Duty);	//ռ�ձ����990������
		ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,0);	   		//ռ�ձ����990������
		ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,MOTOR_Duty);
		ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,0);
//		DataScope_Get_Channel_Data(MOTOR_Duty, 2);		//���ٶ�д��ͨ�� 2
	}
	else
	{
		MOTOR_Duty = range_protect(MOTOR_Duty, -900, 0);	//�޷�����
					//�����ת
		ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,0);	   			//ռ�ձ����990������
		ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,-MOTOR_Duty);	//ռ�ձ����990������
//		DataScope_Get_Channel_Data(MOTOR_Duty, 2);  		//���ٶ�д��ͨ�� 2
	}
//	DataScope_Get_Channel_Data( MOTOR_Speed, 1);//���ٶ�д��ͨ�� 1
}

/******* ����ٶȲ��� ********/
void speed_measure()
{
	int16 Pulses;
	
	Pulses = ftm_quad_get(FTM1);//��ȡFTM �������� ��������(������ʾ������)	 
	ftm_quad_clean(FTM1);   	//��������Ĵ������� 

	MOTOR_Speed = Pulses;	//���ӵ�ǰ��ʵ���ٶ�	
	//save_var(VAR6, MOTOR_Speed);
	MOTOR_Control();
}

void Start_Control(void)
{
	static uchar Start_OK = 0;
	static uchar Ready_Stop = 0;
	static uint16 No_Start_Line_Count = 0;
	
	if (Run_Flag)
	{									/** ���ܽ׶μ�� **/
		if (!Starting_Line_Flag && !Start_OK)	//û�м�⵽��������δ�ɹ�����
		{
			No_Start_Line_Count++;			//�൱����ʱԼ5s
			if (No_Start_Line_Count >= 200)	//����200��û�м�⵽�����ߣ���������ʱ�Ĺ����쳣����
			{
				No_Start_Line_Count = 0;
				Start_OK = 1;	//�����ɹ�
			}
		}
										/** �����׶μ�� **/
		if (Start_OK && Starting_Line_Flag)	//�ɹ����ܺ��⵽�յ���
		{
			Ready_Stop = 1;	//׼��ͣ��
		}
		
		if (Ready_Stop)
		{
			if (!Starting_Line_Flag)	/** ��⵽ͣ���ߺ���ʱһ��ʱ��ͣ�� **/
			{
				No_Start_Line_Count++;
				if (No_Start_Line_Count >= 10 && Game_End)	//����30��û�м�⵽�����ߣ�Լ��ʱ1s
				{
					No_Start_Line_Count = 0;
					Run_Flag = 0;			//ͣ��
					Start_OK = 0;			//��������ɹ���־λ
					Ready_Stop = 0;			//���׼��ͣ����־λ
//					led(LED_MAX,LED_OFF);	//�ر�LEDָʾ��
					led(LED2,LED_OFF);		//�ر�LEDָʾ��
					led(LED3,LED_OFF);		//�ر�LEDָʾ��
				}
			}
		}
	}
}


/******** �޷����� *********/
int32 range_protect(int32 duty, int32 min, int32 max)//�޷�����
{
	if (duty >= max)
	{
		return max;
	}
	if (duty <= min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}