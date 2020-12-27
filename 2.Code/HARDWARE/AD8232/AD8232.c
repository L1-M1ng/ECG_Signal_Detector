#include "AD8232.h"
#include "delay.h"
#include "usart.h"
 
//��ʼ������������
void AD8232_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);//ʹ��PORTFʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//PF8 anolog����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	Adc_Init();
}
//��ȡAD8232��ֵ

u8 AD8232_Get_Val(void)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<AD8232_READ_TIMES;t++)
	{
		temp_val+=Get_Adc(AD8232_ADC_CHX);	//��ȡADCֵ
		delay_ms(5);
	}
	temp_val/=AD8232_READ_TIMES;//�õ�ƽ��ֵ 
	printf("%d\r\n",temp_val);
	//if(temp_val>4096)temp_val=4096;
	return temp_val/26;//(u8)(160-(temp_val/26));
}












