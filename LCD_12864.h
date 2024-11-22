/*********************LCD12864ͷ�ļ�***************************/

#ifndef __LCD_12864_H__
#define __LCD_12864_H__



//LCD12864����ԭ������

/*void lcd_init();								//��ʼ��
bit  lcd_busy();								//��æ
void lcd_wcmd(unsigned char cmd);				//д����
void lcd_wdat(unsigned char dat);				//д����
void lcd_pos(unsigned char X,unsigned char Y);	//λ��
void clr_screen();								//����

*/

#include "reg51.h"
#include "intrins.h"


#define LCD_data  P0       //���ݿ�

sbit LCD_RS  =  P2^6;      //�Ĵ���ѡ������ 
sbit LCD_RW  =  P2^5;      //Һ����/д����
sbit LCD_EN  =  P2^7;      //Һ��ʹ�ܿ���
sbit LCD_PSB =  P3^2;      //��/����ʽ����
sbit LCD_RST =  P3^4;      //Һ����λ�˿�'

void  Delay(unsigned char x)
{
	unsigned char i,j;
	for(i=x;i>0;i--)
		for(j=110;j>0;j--);
}




//���LCDæ״̬ , lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ� 
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


//дָ�����ݵ�LCD , RS=L��RW=L��E=�����壬D0-D7=ָ���롣
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

//д��ʾ���ݵ�LCD ,RS=H��RW=L��E=�����壬D0-D7=���ݡ�
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

// LCD��ʼ���趨 
void lcd_init()
{ 
    LCD_PSB =1;
    LCD_RST = 0;		 //Һ����λ
    Delay(3);                   
    LCD_RST = 1;      
    Delay(3);
    lcd_wcmd(0x34);      //����ָ�����
    Delay(5);
    lcd_wcmd(0x30);      //����ָ�����
    Delay(5);
    lcd_wcmd(0x0C);      //��ʾ�����ع��
    Delay(5);
    lcd_wcmd(0x01);      //���LCD����ʾ����
    Delay(5);
}

//�趨��ʾλ��
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
   lcd_wcmd(pos); //��ʾ��ַ
}

// ��������  
void  clr_screen() 
{
   lcd_wcmd(0x34);//����ָ����� 
   lcd_wcmd(0x30);//����ָ�����
   lcd_wcmd(0x01);//����    
} 















#endif
