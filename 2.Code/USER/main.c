#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"
#include "spi.h"
#include "adc.h"
#include "AD8232.h"
#include "timer.h"


 int main(void)
 { 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	
	uart_init(115200); 
	delay_init();	    	 //延时函数初始化	
	Adc_Init();					//初始化ADC
	LCD_Init();			   	//初始化LCD 	
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
	LCD_Draw_ColorPoint(120,120,BLACK);
	TIM2_Init(10,7200);//分频后10kHz，计数10次，1ms
	TIM3_Init(65535,7200);//分频后10kHz(0.1ms),用于记录两个脉搏之间的时间IBI
 	while(1)
	{

	} 
}



























