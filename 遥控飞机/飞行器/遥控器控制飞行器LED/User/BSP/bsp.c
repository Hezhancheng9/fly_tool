#include "bsp.h"


void LED_Config()
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_Structure.GPIO_Pin =  GPIO_Pin_3;                        //配置管脚
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;             //翻转速度
    GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;              //输出模式
    GPIO_Init(GPIOB, &GPIO_Structure); 
}

void delay(uint16_t n)
{
    uint16_t i,j;
    for(i=0;i<n;i++)
        for(j=0;j<8888;j++);
}


void BSP_Init(void)
{
    LED_Config();                //LED配置函数
    SPI1_Init();                //SPI配置函数 配置NRF24L01接口
    NRF24L01_Init(40,TX);         // NRF24L01配置函数 选择40通道
    NRF24L01_Check();              //检测NRF24L01是否正常
} 
