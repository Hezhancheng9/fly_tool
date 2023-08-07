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
        for(j=0;j<8500;j++);
}


void BSP_Int(void)
{
    Uart1_Init(115200);//串口配置函数 115200代表波特率为115200
    ADC1_Init();//ADC初始化函数
} 


float BAT_Val;                    //电池电压变量
char UTX_Buf[50];                 //串口数据发送数组
void Bat_Vol_Send(void) 
{
     BAT_Val = (ADC_Value[3] * 3.3) / 4096;        //计算电池电压
     sprintf(UTX_Buf,"The Volatage is: %0.2f V \r\n",BAT_Val);
     PrintString(UTX_Buf); //串口发送数据
         PrintString("1234567"); //串口发送数据
}

