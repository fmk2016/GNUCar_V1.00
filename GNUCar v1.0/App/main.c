/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.2
 * @date       2014-10-04
 */
#include "include.h"
#include "test.h"
#include "MK60_it.h"

uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
                    //������Ҫ��ά���飬ֻ��Ҫ�ĳ� uint8 img[CAMERA_H][CAMERA_W];
                    //imgbuff�ǲɼ��Ļ�������img�ǽ�ѹ��Ļ�������imgbuff���ڲɼ�ͼ��img����ͼ����.
int32 S_D5_Duty = 8610;  	//(3330��4480��5630)

void main()
{
    uchar Point = 40; //Ŀ��������
    uint8 Mid_Count;  //����ʶ�𵽵��е�����
    
    //UART_TEST();
    //LED_TEST();
    //MOTOR_TEST();
    
    camera_init(imgbuff);
    //SCCB_WriteByte (OV7725_CNST, 45);
    motorinit();
     
    set_vector_handler(PORTA_VECTORn, PORTA_IRQHandler); //����PORTA���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn, DMA0_IRQHandler);

    while(1)
    {
        
        camera_get_img();
        img_extract(img, imgbuff,CAMERA_SIZE);	//��ѹ
        Mid_Count = Image_GetLine(img);	//ͼ��������õ��е�����
        Point = Point_Weight();				//ʹ�ü�Ȩƽ����ȡĿ��������
        S_D5_Duty = PlacePID_Control(&S_D5_PID, 40, Point);	//ʹ��λ��ʽPID����
        S_D5_Duty = range_protect(S_D5_Duty, 8410, 8810);
        
        ftm_pwm_duty(FTM1, FTM_CH0, S_D5_Duty);			//�޸Ķ��ռ�ձ�5404 5540*/
        //ftm_pwm_duty(FTM1, FTM_CH0, 8610);
        vcan_sendimg(imgbuff,CAMERA_SIZE);
      
        
    }
}

