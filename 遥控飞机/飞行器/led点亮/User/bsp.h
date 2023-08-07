#ifndef _BSP_H
#define _BSP_H
#include "stm32f10x.h"


#define LED2_GPIO GPIOB
#define LED2_Pin GPIO_Pin_3
#define LED2_ON LED2_GPIO->BRR=LED2_Pin
#define LED2_OFF LED2_GPIO->BSRR=LED2_Pin


void LED_Config();

#endif

