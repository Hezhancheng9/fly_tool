#include "bsp.h"


void buzzer_init(void)
{
    GPIO_InitTypeDef GPIO_Structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_Structure.GPIO_Pin = Bee_Pin;    
    GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(Bee_GPIO, &GPIO_Structure);
}
void Delay_buzzer(uint16_t n)
{
    uint16_t i,j;
    for(i=0;i<n;i++)
        for(j=0;j<8888;j++);
}

