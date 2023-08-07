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

void BSP_Init()
{
    ADC1_Init();           //ADC��ʼ��
    SPI2_Init();               //SPI��ʼ������
    NRF24L01_Init(40,RX);    //NRF24L01��ʼ������
    NRF24L01_Check();        //���NRF24L01�Ƿ�����
} 
void LED_Ctrl()
{
      Rc_Filter(&Rc,&Filter_Rc);                        
      if(Filter_Rc.THROTTLE < 1600) 
      {
          LED2_ON();          //ҡ���°� LED����
      }
        else
           LED2_OFF();                             //ҡ���ϰ� LEDϨ��        
        
       if(Filter_Rc.YAW<1600)
       {
           LED3_ON();
       }else
       {
           LED3_OFF();
       }
}


void RC_transfer(void)             //��������ң��ƫ����
{
    uint8_t    data[32];

    Rc_Filter(&Rc, &Filter_Rc);    //����ң��ָ��+�˲�
    if( Filter_Rc.THROTTLE < 1500)    //ҡ���ϰ� LED����
    {
        data[0] = RC_UP;
        NRF_Send_TX( data, 32 );
    }
    else    //ҡ���°� LEDϨ��
    {
        data[0] = RC_DOWN;
        NRF_Send_TX( data, 32 );
    }
}

