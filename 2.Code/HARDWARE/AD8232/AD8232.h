#ifndef __AD8232_H
#define __AD8232_H	
#include "sys.h" 
#include "adc.h" 
//////////////////////////////////////////////////////////////////////////////////	 

  
#define AD8232_READ_TIMES	5	//����ȡƽ��ֵ�Ķ�ȡ����
#define AD8232_ADC_CHX		ADC_Channel_13	//����AD8232���ڵ�ADCͨ�����
    
void AD8232_Init(void); 				//��ʼ��AD8232
u8 AD8232_Get_Val(void);				//��ȡAD8232���ص�adcֵ
#endif 





















