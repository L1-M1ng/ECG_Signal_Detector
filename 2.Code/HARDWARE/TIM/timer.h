#ifndef __TIMER_H
#define __TIMER_H

#include "stdio.h"	
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"



void TIM1_Init(u16 arr,u16 psc);
void TIM1_UP_IRQHandler(void);
void TIM2_Init(u16 arr,u16 psc);
void TIM2_IRQHandler(void);
#endif


