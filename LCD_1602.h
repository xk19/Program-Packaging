
//////////////////////////////LCD1602Һ����ʾͷ�ļ�///////////////////////////
/*******************************Auth0r:    lake_81**************************/
/*******************************************************
���а��������º�����
LCD_init(void) 1602��ʼ������
write_com(uchar)  1602д����� ���磺write_com(0x01);    
write_char(x,y,'_') 1602д���ַ����� ���磺write_char(5,0,'A');
write_string(x,y,"___")д���ַ����������磺write_string(1,1,"I am lake_81");
˵����x������,ȡֵΪ1-16��y�����У�ȡֵΪ0��1��
********************************************************/ 
#ifndef __LCD_1602_H__
#define __LCD_1602_H__

#include "reg51.h"

#define uchar unsigned char //8   0-255
#define uint  unsigned int  //16  0-65535



sbit EN= P2^2;   //��EN���ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ��ִ�����
sbit RW= P2^1;   //RWΪ��д�ź��ߣ�1=��������0=д������
sbit RS= P2^0;   //RSΪ�Ĵ���ѡ��1=���ݼĴ�����0=ָ��Ĵ�����
                   //��RS=RW=0����д��ָ�������ʾ��ַ��
                   //��RS=0��RW=1���Զ�æ�źţ�
                   //��RS=1��RW=0����д�����ݡ�

//delayLCD ��ʱ����
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
//write_com  1602д�����     /*  write_com(0x01) �������   */
void write_com(uchar com)         
{
	RS = 0;
	RW = 0;
	EN = 1;
	P0 = com;
	delayLCD(20);
	EN = 0;	
}
//write_date 1602д���ݺ�����Ƕ����д�ַ����ַ�����������                                              */
void write_date(uchar date)
{	
	RS = 1;
	RW = 0;
	EN = 1;
	P0 = date;
	delayLCD(20);
	EN = 0;	
}
//д���ַ�������
//˵����x�����У�y�����У�ȡֵΪ0��1�����磺write_string(1,1,"I am lake_81");��ʾЧ������
/*
            __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __    
            H  e  l  l  o  ,  w  o  r  l  d  !
*/
void write_string(uchar x,uchar y,uchar *s) 
{     
	if (y == 0) 
	{     
	     write_com(0x80 + x);     //��ʾ��һ��   0x80�ǵ�һ�е�һ���ĵ�ַ��
 	}
    else 
 	{      
 	     write_com(0xC0 + x);     //��ʾ�ڶ���   0xC0�ǵڶ��е�һ���ĵ�ַ��
 	}        
    while (*s) 
 	{     
         write_date( *s);     
         s ++;     
 	}
}
//д���ַ�����
//˵����x�����У�y�����У�ȡֵΪ0��1�����磺write_char(5,0,'A');��ʾЧ������
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

//LCD_init 1602��ʼ������,�Լ��������ã��ɸ�����Ҫ����ѡ��
void LCD_init(void)
{
	write_com(0x38);//��ʾģʽ����
	delayLCD(1);
	write_com(0x0f);
	delayLCD(1);
	write_com(0x06);//��ʾ����ƶ�����
	delayLCD(1);
	write_com(0x0C);//��ʾ�����������
	write_com(0x01);//����
	delayLCD(1);	
}
/**************************************************************************/
#endif
