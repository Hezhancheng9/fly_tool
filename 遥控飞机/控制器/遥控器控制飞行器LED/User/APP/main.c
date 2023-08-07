
#include "stm32f10x.h"
#include "bsp.h"



int main(void)
{
	BSP_Int();
    while(1)
    {
        RC_transfer();
        delay(200);
    }
}
