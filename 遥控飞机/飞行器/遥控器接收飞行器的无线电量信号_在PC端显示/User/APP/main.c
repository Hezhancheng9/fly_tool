
#include "stm32f10x.h"
#include "bsp.h"

static uint8_t data[32]; //�������ݷ��ͻ�����
float BAT_Val;             //��������ص�ѹ

void Bat_Vol_NRF_Tx(void) 
{
   BAT_Val = (ADC_Value[1] * 3.3) / 4096;
      sprintf(data,"Val:%0.2f V",BAT_Val);
      NRF_Send_TX(data,32);     //data �����ͻ����� 32���������ݸ���
}

int main(void)
{
    BSP_Int();           //�������ú�ADC�����Ӻ���
    while(1)
    {
        Bat_Vol_NRF_Tx();  //��ص�ѹ����ͷ����Ӻ���
        delay(500);      //��ʱ����
    }
}

