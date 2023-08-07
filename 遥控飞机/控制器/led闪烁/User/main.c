#include "stm32f10x.h"
#include "bsp.h"



int main(void)
{
    LED_Config();
    while(1)
    {
        LED2_ON();
        delay(100);
        LED2_OFF();
        delay(100);
    }
}

/*********************************************END OF FILE**********************/

