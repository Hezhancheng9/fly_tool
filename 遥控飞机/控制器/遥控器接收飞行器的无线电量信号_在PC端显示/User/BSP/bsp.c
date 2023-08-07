#include "bsp.h"
#include "struct_all.h"
#include "Filter.h"


void LED_Config()
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //����ʱ��

    GPIO_Structure.GPIO_Pin =  GPIO_Pin_11;                        //���ùܽ�
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;             //��ת�ٶ�
    GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;              //���ģʽ
    GPIO_Init(GPIOB, &GPIO_Structure); 
}

void delay(uint16_t n)
{
    uint16_t i,j;
    for(i=0;i<n;i++)
        for(j=0;j<8888;j++);
}

extern uint8_t NRF24L01_RXDATA[32];    //���߽��ջ�����
void Uartx_Send(void)
{
    NRF24L01_IRQ();                    //���߽�������
    PrintString(NRF24L01_RXDATA);       //���ڷ���������PC
    PrintString("\r\n");                //���ڷ��ͻس����з�
}

