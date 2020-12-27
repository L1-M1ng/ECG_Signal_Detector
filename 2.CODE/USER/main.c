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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	
	uart_init(115200); 
	delay_init();	    	 //��ʱ������ʼ��	
	Adc_Init();					//��ʼ��ADC
//	PAout(10)=1;  //���3.3V���ĵ�ģ�鹩�� 
	LCD_Init();			   	//��ʼ��LCD 	
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
	TIM2_Init(10,7200);//��Ƶ��10kHz������10�Σ�1ms
	TIM3_Init(65535,7200);//��Ƶ��10kHz(0.1ms),���ڼ�¼��������֮���ʱ��IBI
 	while(1)
	{
//		Heart_Beat_Signal_old = Heart_Beat_Signal; //������һ������ 
//		Heart_Beat_Signal_Latest=AD8232_Get_Val();//Get_Adc(AD8232_ADC_CHX)/41;
//		//printf("%d\r\n",Heart_Beat_Signal_Latest);
//		Heart_Beat_Signal=Heart_Beat_Signal*0+Heart_Beat_Signal_Latest*1;
//		POINT_COLOR = BLUE;
//		LCD_DrawLine(x_point_location,200-Heart_Beat_Signal_old,x_point_location+3,200-Heart_Beat_Signal);	
////		LCD_Draw_ColorPoint(x_point_location,200-Heart_Beat_Signal*1.6,BLUE);
////		Heart_Beat_Signal=Heart_Beat_Signal_Latest;
//		x_point_location=x_point_location+3;
//		if(x_point_location>=239)
//		{
//			x_point_location=0;
//			LCD_Clear(WHITE);
//			POINT_COLOR = BLACK;
//			LCD_DrawLine(0,40,240,40); //top border line
//			LCD_DrawLine(0,200,240,200);  //bottom border line
//			LCD_DrawLine(0,120,240,120);	//middle line
//			LCD_ShowString(0, 41, 240, 16, 16, "3.3V");
//			LCD_ShowString(0, 201, 240, 16, 16, "0V");
//			LCD_ShowString(0, 121, 240, 16, 16, "1.15V");
//		}
		//printf("%d\r\n",Heart_Beat_Signal);
		//LCD_ShowxNum(0, 0, Heart_Beat_Signal, 3, 32, 0); //��һ��adc����ʾһ����ֵ��Ӱ��adc��ֵ��׼ȷ��
		//delay_ms(1000);
	} 
}



























