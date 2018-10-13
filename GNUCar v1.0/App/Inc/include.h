#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "math.h"
/*
 * Include 用户自定义的头文件
 */
#include  "PID.h"
#include  "init.h"
#include  "Control.h"
#include  "Handle.h"
//#include "PORT_cfg.h"

/*
 *
 * 通用库头文件
 * 
 */
#include  "common.h"
//#include  "MK60_wdog.h"
#include  "MK60_gpio.h"     //IO口操作
#include  "MK60_uart.h"     //串口
#include  "MK60_SysTick.h"
#include  "MK60_lptmr.h"    //低功耗定时器(延时)
#include  "MK60_pit.h"      //PIT
#include  "MK60_FLASH.h"    //FLASH
#include  "MK60_ftm.h"
#include  "MK60_it.h"

/*
 *板级
 */
#include  "VCAN_SCCB.h"
#include  "VCAN_camera.h"
#include  "VCAN_OV7725_Eagle.h"
#include  "VCAN_OV7725_REG.h"
#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY
#include  "VCAN_computer.h"     //多功能调试助手





#endif  //__INCLUDE_H__
