#include "stm32f10x.h"
#include "bsp.h"



int main(void)
{
    buzzer_init();
    while(1)
    {
        Bee_ON;
        Delay_buzzer(1000);
        Bee_OFF;
    }
    
}

/*********************************************END OF FILE**********************/

