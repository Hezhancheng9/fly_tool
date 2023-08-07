#include "bsp.h"
#include "struct_all.h"
#include "Filter.h"


void LED_Config()
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //开启时钟

    GPIO_Structure.GPIO_Pin =  GPIO_Pin_11;                        //配置管脚
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

extern uint8_t NRF24L01_RXDATA[32];    //无线接收缓冲区
void Uartx_Send(void)
{
    NRF24L01_IRQ();                    //无线接收数据
    PrintString(NRF24L01_RXDATA);       //串口发送数据至PC
    PrintString("\r\n");                //串口发送回车换行符
}

