/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.2
 * @date       2014-10-04
 */
#include "include.h"
#include "test.h"
#include "MK60_it.h"

uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_W*CAMERA_H];                           //由于鹰眼摄像头是一字节8个像素，因而需要解压为 1字节1个像素，方便处理
                    //假如需要二维数组，只需要改成 uint8 img[CAMERA_H][CAMERA_W];
                    //imgbuff是采集的缓冲区，img是解压后的缓冲区。imgbuff用于采集图像，img用于图像处理.
int32 S_D5_Duty = 8610;  	//(3330—4480—5630)

void main()
{
    uchar Point = 40; //目标点横坐标
    uint8 Mid_Count;  //保存识别到的中点数量
    
    //UART_TEST();
    //LED_TEST();
    //MOTOR_TEST();
    
    camera_init(imgbuff);
    //SCCB_WriteByte (OV7725_CNST, 45);
    motorinit();
     
    set_vector_handler(PORTA_VECTORn, PORTA_IRQHandler); //设置PORTA的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn, DMA0_IRQHandler);

    while(1)
    {
        
        camera_get_img();
        img_extract(img, imgbuff,CAMERA_SIZE);	//解压
        Mid_Count = Image_GetLine(img);	//图像分析，得到中点数量
        Point = Point_Weight();				//使用加权平均或取目标点横坐标
        S_D5_Duty = PlacePID_Control(&S_D5_PID, 40, Point);	//使用位置式PID解算
        S_D5_Duty = range_protect(S_D5_Duty, 8410, 8810);
        
        ftm_pwm_duty(FTM1, FTM_CH0, S_D5_Duty);			//修改舵机占空比5404 5540*/
        //ftm_pwm_duty(FTM1, FTM_CH0, 8610);
        vcan_sendimg(imgbuff,CAMERA_SIZE);
      
        
    }
}

