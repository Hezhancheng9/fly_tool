
#include "stm32f10x.h"
#include "bsp.h"

static uint8_t data[32]; //无线数据发送缓冲区
float BAT_Val;             //飞行器电池电压

void Bat_Vol_NRF_Tx(void) 
{
   BAT_Val = (ADC_Value[1] * 3.3) / 4096;
      sprintf(data,"Val:%0.2f V",BAT_Val);
      NRF_Send_TX(data,32);     //data ：发送缓冲区 32：发送数据个数
}

int main(void)
{
    BSP_Int();           //串口配置和ADC配置子函数
    while(1)
    {
        Bat_Vol_NRF_Tx();  //电池电压计算和发送子函数
        delay(500);      //延时函数
    }
}

