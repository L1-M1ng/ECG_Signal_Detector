#include "AD8232.h"
#include "delay.h"
#include "usart.h"
 
//初始化心跳传感器
void AD8232_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//使能PORTF时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PF8 anolog输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	Adc_Init();
}
//读取AD8232的值

u8 AD8232_Get_Val(void)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<AD8232_READ_TIMES;t++)
	{
		temp_val+=Get_Adc(AD8232_ADC_CHX);	//读取ADC值
		delay_ms(5);
	}
	temp_val/=AD8232_READ_TIMES;//得到平均值 
	printf("%d\r\n",temp_val);
	//if(temp_val>4096)temp_val=4096;
	return temp_val/26;//(u8)(160-(temp_val/26));
}












