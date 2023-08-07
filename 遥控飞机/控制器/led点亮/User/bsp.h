#ifndef _BSP_H
#define _BSP_H
#include "stm32f10x.h"


#define LED2_ON()    GPIO_ResetBits(GPIOB,GPIO_Pin_11 | GPIO_Pin_12);
#define LED2_OFF()   GPIO_SetBits(GPIOB<GPIO_Pin_11);


void LED_Config();

#endif

