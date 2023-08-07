
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

void RC_Send_CMD(void)
{
    uint8_t    data[32];                      //���巢�ͻ���
    u8 temp;
    Rc_Filter(&Rc, &Filter_Rc);             //����ң��ָ��+�˲�

    if(Filter_Rc.THROTTLE  >= 1500)
    {
        temp = Filter_Rc.THROTTLE / 10;   //������ȡֵ��Χѹ���� 150-200    
        data[0] = temp;                       //��������
        NRF_Send_TX( data, 32 );
    }
    else
    {
        data[0] = 0    ;                       //����0��ʾ��ʱ��������
        NRF_Send_TX( data, 32 );
    }
}

int main(void)
{
    BSP_Int();    //�ײ�������ʼ��
    while(1)
    {
     //   RC_Send_CMD();
     //   delay(200);
        Uart_Check();//�����ڽ��յ�������if(Count 2ms>=1)
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