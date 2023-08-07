#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"
#include "struct_all.h"
#include "Filter.h"

#define LED2_ON()    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
#define LED2_OFF()   GPIO_SetBits(GPIOB,GPIO_Pin_11);

#define LED3_ON()    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
#define LED3_OFF()   GPIO_SetBits(GPIOB,GPIO_Pin_12);

void LED_Config(void);
void delay(uint16_t n);
void BSP_Int(void);
void LED_Ctrl(void);
void Bat_Vol_Send(void);
#endif

