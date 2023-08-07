
#include "stm32f10x.h"
#include "bsp.h"

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

void RC_transfer(void)
{
    uint8_t    data[32];

    Rc_Filter(&Rc, &Filter_Rc);    //遥控器数据滤波¨
    
    data[0] = Filter_Rc.THROTTLE & 0xFF ;    
    
    data[1] =(Filter_Rc.THROTTLE >> 8)& 0xFF;
    
    NRF_Send_TX( data, 32 );
}



int main(void)
{
    BSP_Int();    //硬件初始化
    while(1)
    {
        RC_transfer();
        delay(200);
    }
}