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
        for(j=0;j<8500;j++);
}


void BSP_Int(void)
{
    Uart1_Init(115200);//�������ú��� 115200��������Ϊ115200
    ADC1_Init();//ADC��ʼ������
} 


float BAT_Val;                    //��ص�ѹ����
char UTX_Buf[50];                 //�������ݷ�������
void Bat_Vol_Send(void) 
{
     BAT_Val = (ADC_Value[3] * 3.3) / 4096;        //�����ص�ѹ
     sprintf(UTX_Buf,"The Volatage is: %0.2f V \r\n",BAT_Val);
     PrintString(UTX_Buf); //���ڷ�������
         PrintString("1234567"); //���ڷ�������
}

