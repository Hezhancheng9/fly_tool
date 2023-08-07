#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"
#include "struct_all.h"
#include "Filter.h"
#include "Tasks.h"
#include "Maths.h"
#include "struct_all.h"

#define RC_UP 0xAA
#define RC_DOWN 0x55

#define LED2_ON()    GPIO_ResetBits(GPIOB,GPIO_Pin_11);
#define LED2_OFF()   GPIO_SetBits(GPIOB,GPIO_Pin_11);

#define LED3_ON()    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
#define LED3_OFF()   GPIO_SetBits(GPIOB,GPIO_Pin_12);

void LED_Config(void);
void delay(uint16_t n);
void BSP_Init(void);
void LED_Ctrl(void);
void RC_transfer(void);
#endif

