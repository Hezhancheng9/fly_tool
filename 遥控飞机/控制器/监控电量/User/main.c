#include "stm32f10x.h"
#include "bsp.h"



int main(void)
{
    BSP_Int();
    while(1)
    {
        Bat_Vol_Send();  //��ص�ѹ����ͷ����Ӻ���
        delay(500);       //��ʱ����
    }
}

/*********************************************END OF FILE**********************/

