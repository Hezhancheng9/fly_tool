
#include "stm32f10x.h"
#include "bsp.h"

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

void RC_transfer(void)
{
    uint8_t    data[32];

    Rc_Filter(&Rc, &Filter_Rc);    //ң���������˲���
    
    data[0] = Filter_Rc.THROTTLE & 0xFF ;    
    
    data[1] =(Filter_Rc.THROTTLE >> 8)& 0xFF;
    
    NRF_Send_TX( data, 32 );
}



int main(void)
{
    BSP_Int();    //Ӳ����ʼ��
    while(1)
    {
        RC_transfer();
        delay(200);
    }
}