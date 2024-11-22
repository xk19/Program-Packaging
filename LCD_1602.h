
//////////////////////////////LCD1602液晶显示头文件///////////////////////////
/*******************************Auth0r:    lake_81**************************/
/*******************************************************
其中包含有以下函数：
LCD_init(void) 1602初始化函数
write_com(uchar)  1602写命令函数 例如：write_com(0x01);    
write_char(x,y,'_') 1602写入字符函数 例如：write_char(5,0,'A');
write_string(x,y,"___")写入字符串函数例如：write_string(1,1,"I am lake_81");
说明：x代表列,取值为1-16；y代表行，取值为0或1；
********************************************************/ 
#ifndef __LCD_1602_H__
#define __LCD_1602_H__

#include "reg51.h"

#define uchar unsigned char //8   0-255
#define uint  unsigned int  //16  0-65535



sbit EN= P2^2;   //当EN端由高电平跳变成低电平时，液晶模块执行命令。
sbit RW= P2^1;   //RW为读写信号线，1=读操作，0=写操作。
sbit RS= P2^0;   //RS为寄存器选择，1=数据寄存器、0=指令寄存器。
                   //当RS=RW=0可以写入指令或者显示地址，
                   //当RS=0，RW=1可以读忙信号，
                   //当RS=1，RW=0可以写入数据。

//delayLCD 延时函数
void delayLCD(uint x)
{
	uint a,b;
	for(a = x;a > 0;a--)
    {
		for(b = 10;b > 0;b--) 
        {
            ;
        }
    }
}
//write_com  1602写命令函数     /*  write_com(0x01) 清屏语句   */
void write_com(uchar com)         
{
	RS = 0;
	RW = 0;
	EN = 1;
	P0 = com;
	delayLCD(20);
	EN = 0;	
}
//write_date 1602写数据函数，嵌套在写字符、字符串函数里面                                              */
void write_date(uchar date)
{	
	RS = 1;
	RW = 0;
	EN = 1;
	P0 = date;
	delayLCD(20);
	EN = 0;	
}
//写入字符串函数
//说明：x代表列；y代表行，取值为0或1；例如：write_string(1,1,"I am lake_81");显示效果如下
/*
            __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __    
            H  e  l  l  o  ,  w  o  r  l  d  !
*/
void write_string(uchar x,uchar y,uchar *s) 
{     
	if (y == 0) 
	{     
	     write_com(0x80 + x);     //表示第一行   0x80是第一行第一个的地址，
 	}
    else 
 	{      
 	     write_com(0xC0 + x);     //表示第二行   0xC0是第二行第一个的地址，
 	}        
    while (*s) 
 	{     
         write_date( *s);     
         s ++;     
 	}
}
//写入字符函数
//说明：x代表列；y代表行，取值为0或1；例如：write_char(5,0,'A');显示效果如下
/*
            __ __ __ __ A  __ __ __ __ __ __ __ __ __ __ __ __
            __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __    
*/
void write_char(uchar x,uchar y,uchar Data) 
{     
    if (y == 0) 
 	{     
 	    write_com(0x80 + x);     
 	}    
    else 
 	{     
 	    write_com(0xC0 + x);     
 	}        
        write_date(Data);  
}

//LCD_init 1602初始化函数,以及其他设置，可根据需要自行选择
void LCD_init(void)
{
	write_com(0x38);//显示模式设置
	delayLCD(1);
	write_com(0x0f);
	delayLCD(1);
	write_com(0x06);//显示光标移动设置
	delayLCD(1);
	write_com(0x0C);//显示开及光标设置
	write_com(0x01);//清屏
	delayLCD(1);	
}
/**************************************************************************/
#endif
