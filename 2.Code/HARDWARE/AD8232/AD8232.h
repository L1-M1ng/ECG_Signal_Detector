#ifndef __AD8232_H
#define __AD8232_H	
#include "sys.h" 
#include "adc.h" 
//////////////////////////////////////////////////////////////////////////////////	 

  
#define AD8232_READ_TIMES	20	//���������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
#define AD8232_ADC_CHX		ADC_Channel_13	//����������������ڵ�ADCͨ�����
    
void AD8232_Init(void); 				//��ʼ������������
u8 AD8232_Get_Val(void);				//��ȡ������������ֵ
#endif 





















