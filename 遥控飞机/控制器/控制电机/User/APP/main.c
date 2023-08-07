
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

void RC_Send_CMD(void)
{
    uint8_t    data[32];                      //定义发送缓存
    u8 temp;
    Rc_Filter(&Rc, &Filter_Rc);             //计算遥控指令+滤波

    if(Filter_Rc.THROTTLE  >= 1500)
    {
        temp = Filter_Rc.THROTTLE / 10;   //将数据取值范围压缩至 150-200    
        data[0] = temp;                       //发送数据
        NRF_Send_TX( data, 32 );
    }
    else
    {
        data[0] = 0    ;                       //发送0表示此时不起飞离地
        NRF_Send_TX( data, 32 );
    }
}

int main(void)
{
    BSP_Int();    //底层驱动初始化
    while(1)
    {
     //   RC_Send_CMD();
     //   delay(200);
        Uart_Check();//处理串口接收到的数据if(Count 2ms>=1)
        if(Count_2ms>=1)
        {
            Count_2ms = 0;
            Task_500HZ();
        }
        if(Count_10ms>= 5)
        {
            Count_10ms = 0;
            Task_100HZ();
        }
        if(Count_40ms>=20)
        {
            Count_40ms = 0;
            Task_25HZ();
        }
        if(Count_250ms>=125)
        {
            Count_250ms = 0;
            Task_4HZ();
        }
        }
}