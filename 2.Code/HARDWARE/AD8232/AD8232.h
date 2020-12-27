#ifndef __AD8232_H
#define __AD8232_H	
#include "sys.h" 
#include "adc.h" 
//////////////////////////////////////////////////////////////////////////////////	 

  
#define AD8232_READ_TIMES	20	//定义光敏传感器读取次数,读这么多次,然后取平均值
#define AD8232_ADC_CHX		ADC_Channel_13	//定义光敏传感器所在的ADC通道编号
    
void AD8232_Init(void); 				//初始化光敏传感器
u8 AD8232_Get_Val(void);				//读取光敏传感器的值
#endif 





















