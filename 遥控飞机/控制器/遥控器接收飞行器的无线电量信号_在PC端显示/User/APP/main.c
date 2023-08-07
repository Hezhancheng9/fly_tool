
#include "stm32f10x.h"
#include "bsp.h"



int main(void)
{
	BSP_Int();
    while(1)
    {
        void Uartx_Send(void);
        delay(200);
    }
}
