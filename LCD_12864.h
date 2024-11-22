/*********************LCD12864头文件***************************/

#ifndef __LCD_12864_H__
#define __LCD_12864_H__



//LCD12864函数原型声明

/*void lcd_init();								//初始化
bit  lcd_busy();								//判忙
void lcd_wcmd(unsigned char cmd);				//写命令
void lcd_wdat(unsigned char dat);				//写数据
void lcd_pos(unsigned char X,unsigned char Y);	//位置
void clr_screen();								//清屏

*/

#include "reg51.h"
#include "intrins.h"


#define LCD_data  P0       //数据口

sbit LCD_RS  =  P2^6;      //寄存器选择输入 
sbit LCD_RW  =  P2^5;      //液晶读/写控制
sbit LCD_EN  =  P2^7;      //液晶使能控制
sbit LCD_PSB =  P3^2;      //串/并方式控制
sbit LCD_RST =  P3^4;      //液晶复位端口'

void  Delay(unsigned char x)
{
	unsigned char i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}




//检查LCD忙状态 , lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。 
bit lcd_busy()  
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }


//写指令数据到LCD , RS=L，RW=L，E=高脉冲，D0-D7=指令码。
void lcd_wcmd(unsigned char cmd) 
{                          
    while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = cmd;
    _nop_();
    _nop_();     
    LCD_EN = 1;
    LCD_EN = 0; 
}

//写显示数据到LCD ,RS=H，RW=L，E=高脉冲，D0-D7=数据。
void lcd_wdat(unsigned char dat) 
{                          
    while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
	P0 = dat;   
    LCD_EN = 1;
    LCD_EN = 0; 
}

// LCD初始化设定 
void lcd_init()
{ 
    LCD_PSB =1;
    LCD_RST = 0;		 //液晶复位
    Delay(3);                   
    LCD_RST = 1;      
    Delay(3);
    lcd_wcmd(0x34);      //扩充指令操作
    Delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    Delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    Delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    Delay(5);
}

//设定显示位置
void lcd_pos(unsigned char X,unsigned char Y)
{                          
   unsigned char  pos;
   if (X==1)
     {X=0x80;}
   else if (X==2)
     {X=0x90;}
   else if (X==3)
     {X=0x88;}
   else if (X==4)
     {X=0x98;}
   pos = X+Y ; 
   lcd_wcmd(pos); //显示地址
}

// 清屏函数  
void  clr_screen() 
{
   lcd_wcmd(0x34);//扩充指令操作 
   lcd_wcmd(0x30);//基本指令操作
   lcd_wcmd(0x01);//清屏    
} 















#endif
