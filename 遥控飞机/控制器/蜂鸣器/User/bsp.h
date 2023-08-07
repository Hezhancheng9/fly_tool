#ifndef _BUZZER_H_
#define _BUZZER_H_
#include "stm32f10x.h"

#define Bee_GPIO            GPIOB
#define Bee_Pin            GPIO_Pin_10

#define Bee_ON             Bee_GPIO->BSRR  = Bee_Pin //·äÃùÆ÷
#define Bee_OFF            Bee_GPIO->BRR   = Bee_Pin

void Delay_buzzer(uint16_t n);
void buzzer_init(void);

#endif


