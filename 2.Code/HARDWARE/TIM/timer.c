#include "timer.h"


//---------------------------TIM2��ʼ������
//ʱ��ԴΪAPB1��2��  72MHz
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	TIM_TimeBaseStruct.TIM_Prescaler=psc;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=arr;
	TIM_TimeBaseStruct.TIM_ClockDivision= TIM_CKD_DIV2;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);  //����TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ������ж�
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);//���ö�ʱ���ж�
	
	TIM_Cmd(TIM2,ENABLE);
}

//-----------------------------TIM2_UP_IRQn���жϷ�����
void TIM2_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		

	}
}


//---------------------------TIM1��ʼ������
//ʱ��ԴΪAPB2��2��  72MHz
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //ʹ��ʱ��
	
	TIM_TimeBaseStruct.TIM_Prescaler=psc;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=arr;
	TIM_TimeBaseStruct.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);  //����TIM3
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//ʹ������ж�
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);//���ö�ʱ���ж�
	
	
	TIM_Cmd(TIM1,ENABLE);
}

//-----------------------------TIM1_UP_IRQn���жϷ�����
void TIM1_UP_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		
	
	}
}


