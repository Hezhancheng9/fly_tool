#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"
#include "struct_all.h"
#include "Filter.h"
#include "IMU.h"
#include "Tasks.h"
#include "Maths.h"
#include "Control.h"
#include "struct_all.h"




#define LED_ON    GPIOC->BSRR=GPIO_Pin_13;
#define LED_OFF   GPIOC->BRR=GPIO_Pin_13 ;

void LED_Config(void);
void delay(uint16_t n);
void BSP_Init(void);
void Bat_Vol_NRF_Tx(void);

#endif

