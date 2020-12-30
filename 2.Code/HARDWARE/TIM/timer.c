#include "timer.h"


u8 Adc_Buffer[240];
u8 Adc_buffer_Store_Position =1 ;
u8 Beat_Pulse_Max = 0;	//心电信号最大值
u8 Beat_Pulse_Min = 160;	//心电信号最小值
u8 Beat_Pulse_Sum = 0;	//心电信号总值，用于计算均值
u8 Beat_Pulse_Avg = 0;	//心电信号均值
u8 Beat_Pulse_Threshold = 0;	//心电信号阈值
u8 Data_Store_Cnts = 40;
u8 BPM_Measurement_Flag = 0;

u16 x_point_location=0;
u16 y_point_location=0;
u16 Heart_Beat_Signal_old =0;
u16 Heart_Beat_Signal=0; 
u16 Heart_Beat_Signal_Latest=0;

float IBI_Time = 0;
float BPM_Result = 0;
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
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
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

////----------------------------实时更新显示
		Adc_Buffer[Adc_buffer_Store_Position]=AD8232_Get_Val();
		printf("%c",Adc_Buffer[Adc_buffer_Store_Position]);
		POINT_COLOR = BLUE;
		LCD_DrawLine(x_point_location,200-Adc_Buffer[Adc_buffer_Store_Position-1],x_point_location+3,200-Adc_Buffer[Adc_buffer_Store_Position]);	
		Beat_Pulse_Sum+=Adc_Buffer[Adc_buffer_Store_Position];
		
		
		
		if(Adc_buffer_Store_Position>=Data_Store_Cnts-1)
		{
			//-----------------均值计算
			Beat_Pulse_Avg=Beat_Pulse_Sum/40;
			Beat_Pulse_Sum=0;
			
			//-----------------更新阈值
			Beat_Pulse_Threshold = (Beat_Pulse_Max+Beat_Pulse_Min)/2;//(Beat_Pulse_Avg+Beat_Pulse_Max)/2;
			
			
			LCD_ShowxNum(0, 0, Beat_Pulse_Max, 3, 32, 0);
			LCD_ShowxNum(50, 0, Beat_Pulse_Min, 3, 32, 0);
			LCD_ShowxNum(150, 0, Beat_Pulse_Threshold, 3, 32, 0);
			
			//-----------------复位，准备下一轮计算
			Beat_Pulse_Max = 0;
			Beat_Pulse_Min = 160;
			
			Adc_buffer_Store_Position=0;
			Adc_Buffer[0]=Adc_Buffer[Data_Store_Cnts-1];
		}
		else
		{
			//-----------------最大、最小值记录
			if(Adc_Buffer[Adc_buffer_Store_Position]>Beat_Pulse_Max)
			{
				Beat_Pulse_Max=Adc_Buffer[Adc_buffer_Store_Position];
			}
			else if(Adc_Buffer[Adc_buffer_Store_Position]<Beat_Pulse_Min)
			{
				Beat_Pulse_Min=Adc_Buffer[Adc_buffer_Store_Position];
			}
			
			//脉搏检测，计算心率
			if(Beat_Pulse_Threshold!=0)
			{
				if((Adc_Buffer[Adc_buffer_Store_Position-1]<Beat_Pulse_Threshold)&&(Adc_Buffer[Adc_buffer_Store_Position]>Beat_Pulse_Threshold))
				{
					if(BPM_Measurement_Flag==0)
					{	
						BPM_Measurement_Flag=1;
						Clock_Start();
					}
					else
					{
						IBI_Time=Clock_End();
						BPM_Measurement_Flag=0;
						BPM_Result= 60/(IBI_Time*0.0001);
						POINT_COLOR = RED;
						LCD_ShowString(50,201, 240, 32, 32,  "BPM->");
						LCD_ShowxNum(150, 201, BPM_Result, 3, 32, 0);
					}		
				}
				
			}
		}
		
		Adc_buffer_Store_Position++;
		
	
	
		//-----------------控制TFT屏幕画线作标范围，以及刷新画面其他元素
		x_point_location=x_point_location+3;
		if(x_point_location>=239)
		{
			x_point_location=0;
			LCD_Clear(WHITE);
			POINT_COLOR = BLACK;
			LCD_DrawLine(0,40,240,40); //top border line
			LCD_DrawLine(0,200,240,200);  //bottom border line
			LCD_DrawLine(0,120,240,120);	//middle line
			LCD_ShowString(0, 41, 240, 16, 16, "3.3V");
			LCD_ShowString(0, 201, 240, 16, 16, "0V");
			LCD_ShowString(0, 121, 240, 16, 16, "1.15V");

			POINT_COLOR = RED;
			LCD_ShowString(50,201, 240, 32, 32,  "BPM->");
			LCD_ShowxNum(150, 201, BPM_Result, 3, 32, 0);

			POINT_COLOR = BLUE;
			LCD_ShowxNum(0, 0, Beat_Pulse_Max, 3, 32, 0);
			LCD_ShowxNum(50, 0, Beat_Pulse_Min, 3, 32, 0);

		}
		
	}
}

//---------------------------TIM3初始化函数
//时钟源为APB1的2倍  72MHz
//arr：自动重装值
//psc：时钟预分频数
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStruct.TIM_Prescaler=psc;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=arr;
	TIM_TimeBaseStruct.TIM_ClockDivision= TIM_CKD_DIV2;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);  //配置TIM3

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


//计数开始：定时器3
void Clock_Start()
{
	TIM3->CNT=0x00;
	TIM_Cmd(TIM3,ENABLE);
}

//计数结束：定时器3
u32 Clock_End()
{
	u32 result;
	result = TIM3->CNT;
	TIM_Cmd(TIM3,DISABLE);
	return result;
}
