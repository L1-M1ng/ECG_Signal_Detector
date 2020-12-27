#ifndef __LCD_H
#define __LCD_H
#include "sys.h"

extern u16	POINT_COLOR;	//默认画笔颜色
extern u16	BACK_COLOR;		//默认背景颜色

//LCD的宽和高定义
#define LCD_Width 	240
#define LCD_Height 	240

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)



/*
    	LCD_PWR:	PA4
    	LCD_RST:	PA1
    	LCD_DC:		PA6
    	LCD_CS:		PC4
*/
#define	LCD_PWR		PAout(4)
#define	LCD_RST		PAout(1)
#define	LCD_DC		PAout(6)
#define	LCD_CS		PCout(4)


void LCD_Init(void);																	//初始化
void LCD_DisplayOn(void);																//开显示
void LCD_DisplayOff(void);																//关显示
void LCD_Write_HalfWord(const u16 da);													//写半个字节数据到LCD
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);									//设置数据显示区域
void LCD_Clear(u16 color);																//清屏
void LCD_Fill(u16 x_start, u16 y_start, u16 x_end, u16 y_end, u16 color);				//填充单色
void LCD_Draw_Point(u16 x, u16 y);														//画点
void LCD_Draw_ColorPoint(u16 x, u16 y,u16 color);										//画带颜色点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);										//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);									//画矩形
void LCD_Draw_Circle(u16 x0, u16 y0, u8 r);												//画圆
void LCD_ShowChar(u16 x, u16 y, char chr, u8 size);										//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);									//显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);							//显示数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);					//显示字符串
void LCD_Show_Image(u16 x, u16 y, u16 width, u16 height, const u8 *p);					//显示图片
void Display_ALIENTEK_LOGO(u16 x,u16 y);												//显示ALIENTEK LOGO

void Display_Adc_Buffer(u16 *Buffer);

#endif


