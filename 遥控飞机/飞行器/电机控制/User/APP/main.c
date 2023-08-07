
#include "stm32f10x.h"
#include "Motor.h"
#include "SPI_NRF24L01.h"
#include "Tasks.h"
#include "stm32f10x_it.h"


void delay1(uint16_t n)
{
    uint16_t i,j;
    for(i=0;i<n;i++)
        for(j=0;j<8888;j++);
}

void Fly_Ctrl_Func()
{
    u16 Motor_Speed[4];                    //�ĸ����ת������
    u8 Rx_Cmd,i;
    Rx_Cmd = NRF24L01_RXDATA[0];          //����������ָ��                                
    for(i = 0; i < 4; i++)                                                     
    {
     Motor_Speed[i] = (Rx_Cmd * 12) - 1500;    //�ĸ����������ת�ټ���
    }
    Motor_Out(Motor_Speed[0] ,Motor_Speed[1] ,Motor_Speed[2] ,Motor_Speed[3] ); //�ĸ����ת�ٸ�ֵ
}


int main(void)
{ 
    
     BSP_Int();    //�ײ�������ʼ��
    while(1)
    {
        GPIOC->BSRR = GPIO_Pin_13;
       // Fly_Ctrl_Func();
        if(Count_1ms>=1)
        {
            Count_1ms=0;
            Task_1000HZ();
        }
        if(Count_2ms>=2)
        {
            Count_2ms = 0;
            Task_500HZ();
        }
        if(Count_4ms>=4)
        {
            Count_4ms = 0;
            Task_250HZ() ;
        }
    }
}



