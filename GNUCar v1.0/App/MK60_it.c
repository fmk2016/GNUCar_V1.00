/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       MK60_it.c
 * @brief      ɽ��K60 ƽ̨�жϷ�����
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-06-26
 */

#include "MK60_it.h"

void uart5_handler(void)
{
    char ch;
    if(uart_query(UART5) == 1)
    {
        uart_getchar(UART5,&ch);
        uart_putchar(UART5,ch);
    }
}

void PORTA_IRQHandler(void)
{
    camera_vsync();
}

void DMA0_IRQHandler(void)
{
    camera_dma();
}


