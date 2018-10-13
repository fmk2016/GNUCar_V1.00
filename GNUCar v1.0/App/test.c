
#include "include.h"
#include "test.h"
void LED_TEST(void)
{
    gpio_init(PTC16,GPO,0);                         //初始化LED0  ，亮
    gpio_init(PTC17,GPO,0); 
    gpio_init(PTC18,GPO,0); 
    gpio_init(PTC19,GPO,0); 
}
void MOTOR_TEST(void)
{
    gpio_init(PTC1,GPO,0);
    gpio_init(PTC2,GPO,0);
    gpio_init(PTC3,GPO,0);
    gpio_init(PTC4,GPO,0);
    gpio_init(PTB0,GPO,0);
    
    ftm_pwm_init(FTM0, FTM_CH0, 10*1000, 15);
    ftm_pwm_init(FTM0, FTM_CH1, 10*1000, 0);
    ftm_pwm_init(FTM0, FTM_CH2, 10*1000, 0);
    ftm_pwm_init(FTM0, FTM_CH3, 10*1000, 15);
    ftm_pwm_init(FTM1,FTM_CH0,100,8610);
}
void UART_TEST(void)
{
    uart_init(UART5,115200);
    uart_putstr(UART5,"Yinshijia");
    set_vector_handler(UART5_RX_TX_VECTORn,uart5_handler);
    uart_rx_irq_en(UART5);
}
void CAMERA_TESET(void)
{
   
}