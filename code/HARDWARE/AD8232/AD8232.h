#ifndef __AD8232_H
#define __AD8232_H	
#include "sys.h" 
#include "adc.h" 
//////////////////////////////////////////////////////////////////////////////////	 

  
#define AD8232_READ_TIMES	5	//定义取平均值的读取次数
#define AD8232_ADC_CHX		ADC_Channel_13	//定义AD8232所在的ADC通道编号
    
void AD8232_Init(void); 				//初始化AD8232
u8 AD8232_Get_Val(void);				//读取AD8232返回的adc值
#endif 





















