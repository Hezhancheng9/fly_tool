
#include "stm32f10x.h"
#include "bsp.h"

#define RC_UP 0xAA
#define RC_DOWN 0x55

int main(void)
{
    BSP_Int();
    while(1)
    {
       if( NRF24L01_RXDATA[0] == RC_UP )
        {
        //    GPIO_SetBits(GPIOC, GPIO_Pin_13);
            LED_ON;
        }
        else
        {
        //     GPIO_ResetBits(GPIOC,GPIO_Pin_13);
            LED_OFF;
        }
        delay(50);
        
    }
}

