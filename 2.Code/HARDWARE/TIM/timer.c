#include "timer.h"


u8 Adc_Buffer[240];
u8 Adc_buffer_Store_Position =1 ;
u8 Beat_Pulse_Max = 0;	//�ĵ��ź����ֵ
u8 Beat_Pulse_Min = 160;	//�ĵ��ź���Сֵ
u8 Beat_Pulse_Sum = 0;	//�ĵ��ź���ֵ�����ڼ����ֵ
u8 Beat_Pulse_Avg = 0;	//�ĵ��źž�ֵ
u8 Beat_Pulse_Threshold = 0;	//�ĵ��ź���ֵ
u8 Data_Store_Cnts = 40;
u8 BPM_Measurement_Flag = 0;

u16 x_point_location=0;
u16 y_point_location=0;
u16 Heart_Beat_Signal_old =0;
u16 Heart_Beat_Signal=0; 
u16 Heart_Beat_Signal_Latest=0;

float IBI_Time = 0;
float BPM_Result = 0;
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
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
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

////----------------------------ʵʱ������ʾ
		Adc_Buffer[Adc_buffer_Store_Position]=AD8232_Get_Val();
		printf("%c",Adc_Buffer[Adc_buffer_Store_Position]);
		POINT_COLOR = BLUE;
		LCD_DrawLine(x_point_location,200-Adc_Buffer[Adc_buffer_Store_Position-1],x_point_location+3,200-Adc_Buffer[Adc_buffer_Store_Position]);	
		Beat_Pulse_Sum+=Adc_Buffer[Adc_buffer_Store_Position];
		
		
		
		if(Adc_buffer_Store_Position>=Data_Store_Cnts-1)
		{
			//-----------------��ֵ����
			Beat_Pulse_Avg=Beat_Pulse_Sum/40;
			Beat_Pulse_Sum=0;
			
			//-----------------������ֵ
			Beat_Pulse_Threshold = (Beat_Pulse_Max+Beat_Pulse_Min)/2;//(Beat_Pulse_Avg+Beat_Pulse_Max)/2;
			
			
			LCD_ShowxNum(0, 0, Beat_Pulse_Max, 3, 32, 0);
			LCD_ShowxNum(50, 0, Beat_Pulse_Min, 3, 32, 0);
			LCD_ShowxNum(150, 0, Beat_Pulse_Threshold, 3, 32, 0);
			
			//-----------------��λ��׼����һ�ּ���
			Beat_Pulse_Max = 0;
			Beat_Pulse_Min = 160;
			
			Adc_buffer_Store_Position=0;
			Adc_Buffer[0]=Adc_Buffer[Data_Store_Cnts-1];
		}
		else
		{
			//-----------------�����Сֵ��¼
			if(Adc_Buffer[Adc_buffer_Store_Position]>Beat_Pulse_Max)
			{
				Beat_Pulse_Max=Adc_Buffer[Adc_buffer_Store_Position];
			}
			else if(Adc_Buffer[Adc_buffer_Store_Position]<Beat_Pulse_Min)
			{
				Beat_Pulse_Min=Adc_Buffer[Adc_buffer_Store_Position];
			}
			
			//������⣬��������
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
		
	
	
		//-----------------����TFT��Ļ�������귶Χ���Լ�ˢ�»�������Ԫ��
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

//---------------------------TIM3��ʼ������
//ʱ��ԴΪAPB1��2��  72MHz
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStruct.TIM_Prescaler=psc;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_Period=arr;
	TIM_TimeBaseStruct.TIM_ClockDivision= TIM_CKD_DIV2;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);  //����TIM3

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


//������ʼ����ʱ��3
void Clock_Start()
{
	TIM3->CNT=0x00;
	TIM_Cmd(TIM3,ENABLE);
}

//������������ʱ��3
u32 Clock_End()
{
	u32 result;
	result = TIM3->CNT;
	TIM_Cmd(TIM3,DISABLE);
	return result;
}
