#include "bsp.h"


void LED_Config()
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_Structure.GPIO_Pin =  GPIO_Pin_3;                        //���ùܽ�
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;             //��ת�ٶ�
    GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;              //���ģʽ
    GPIO_Init(GPIOB, &GPIO_Structure); 
}


void BSP_Init(void)
{
    LED_Config();                //LED���ú���
    SPI1_Init();                //SPI���ú��� ����NRF24L01�ӿ�
    NRF24L01_Init(40,TX);         // NRF24L01���ú��� ѡ��40ͨ��
    NRF24L01_Check();              //���NRF24L01�Ƿ�����
} 
