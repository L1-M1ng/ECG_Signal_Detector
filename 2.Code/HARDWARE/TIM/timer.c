#include "timer.h"


//---------------------------TIM2初始化函数
//时钟源为APB1的2倍  72MHz
//arr：自动重装值
//psc：时钟预分频数
void TIM2_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	TIM_TimeBaseStruct.TIM_Prescaler=psc;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=arr;
	TIM_TimeBaseStruct.TIM_ClockDivision= TIM_CKD_DIV2;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);  //配置TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能溢出中断
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);//配置定时器中断
	
	TIM_Cmd(TIM2,ENABLE);
}

//-----------------------------TIM2_UP_IRQn的中断服务函数
void TIM2_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		

	}
}


//---------------------------TIM1初始化函数
//时钟源为APB2的2倍  72MHz
//arr：自动重装值
//psc：时钟预分频数
void TIM1_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //使能时钟
	
	TIM_TimeBaseStruct.TIM_Prescaler=psc;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=arr;
	TIM_TimeBaseStruct.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);  //配置TIM3
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//使能溢出中断
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);//配置定时器中断
	
	
	TIM_Cmd(TIM1,ENABLE);
}

//-----------------------------TIM1_UP_IRQn的中断服务函数
void TIM1_UP_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		
	
	}
}


