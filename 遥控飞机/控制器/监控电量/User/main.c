#include "stm32f10x.h"
#include "bsp.h"



int main(void)
{
    BSP_Int();
    while(1)
    {
        Bat_Vol_Send();  //电池电压计算和发送子函数
        delay(500);       //延时函数
    }
}

/*********************************************END OF FILE**********************/

