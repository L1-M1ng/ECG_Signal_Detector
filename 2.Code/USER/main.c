#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "tftlcd.h"
#include "spi.h"
#include "adc.h"
#include "AD8232.h"
#include "timer.h"

u16 x_point_location=0;
u16 y_point_location=0;
u16 Heart_Beat_Signal_old =0;
u16 Heart_Beat_Signal=0; 
u16 Heart_Beat_Signal_Latest=0;

 int main(void)
 { 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	TIM2_Init(100,7200);//10ms
	uart_init(115200); 
	delay_init();	    	 //延时函数初始化	
	Adc_Init();					//初始化ADC
	PAout(10)=1;  //输出3.3V给心电模块供电 
	LCD_Init();			   	//初始化LCD 	
	LCD_Clear(WHITE);
	//Display_ALIENTEK_LOGO(0, 0);
//	POINT_COLOR = RED;
//	BACK_COLOR = WHITE;
//	LCD_ShowString(0, 100, 240, 32, 32, "MINI STM32F1");
//	LCD_ShowString(0, 140, 240, 24, 24, "TFTLCD TEST 240*240");

//	POINT_COLOR = WHITE;
//	BACK_COLOR = BLUE;
//	LCD_ShowString(0, 170, 240, 16, 16, "ATOM@ALIENTEK");
//	LCD_ShowString(0, 200, 240, 12, 12, "2019/1/7");
	LCD_DrawLine(0,40,240,40); //top border line
	LCD_DrawLine(0,200,240,200);  //bottom border line
	LCD_DrawLine(0,120,240,120);	//middle line
	
	LCD_Draw_ColorPoint(120,120,BLACK);
 	while(1)
	{
		Heart_Beat_Signal_old = Heart_Beat_Signal; //保存上一次数据 
		Heart_Beat_Signal_Latest=AD8232_Get_Val();//Get_Adc(AD8232_ADC_CHX)/30;
		//printf("%d\r\n",Heart_Beat_Signal_Latest);
		Heart_Beat_Signal=Heart_Beat_Signal*0.7+Heart_Beat_Signal_Latest*0.3;
		POINT_COLOR = BLUE;
		LCD_DrawLine(x_point_location,Heart_Beat_Signal_old,x_point_location+3,Heart_Beat_Signal);	
//		LCD_Draw_ColorPoint(x_point_location,200-Heart_Beat_Signal*1.6,BLUE);
		Heart_Beat_Signal=Heart_Beat_Signal_Latest;
		x_point_location=x_point_location+3;
		if(x_point_location>=239)
		{
			x_point_location=0;
			LCD_Clear(WHITE);
			POINT_COLOR = BLACK;
			LCD_DrawLine(0,40,240,40); //top border line
			LCD_DrawLine(0,200,240,200);  //bottom border line
			LCD_DrawLine(0,120,240,120);	//middle line
		}
		//printf("%d\r\n",Heart_Beat_Signal);
		//LCD_ShowxNum(0, 0, Heart_Beat_Signal, 3, 32, 0); //读一次adc就显示一次数值会影响adc数值的准确性
		//delay_ms(1000);
	} 
}



























