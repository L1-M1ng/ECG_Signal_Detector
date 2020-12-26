#ifndef __TIMER_H
#define __TIMER_H

#include "stdio.h"	
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "tftlcd.h"
#include "spi.h"
#include "adc.h"
#include "AD8232.h"
#include "timer.h"

extern u16 x_point_location;
extern u16 y_point_location;
extern u16 Heart_Beat_Signal_old;
extern u16 Heart_Beat_Signal;
extern u16 Heart_Beat_Signal_Latest;


void TIM1_Init(u16 arr,u16 psc);
void TIM1_UP_IRQHandler(void);
void TIM2_Init(u16 arr,u16 psc);
void TIM2_IRQHandler(void);
void TIM3_Init(u16 arr,u16 psc);

void Clock_Start(void);
u32 Clock_End(void);
#endif


