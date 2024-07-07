#include"header.h"

void ms_delay(int ms){
	unsigned int a[]={15,60,30,15,15},p;
	p=a[VPBDIV]*1000;
	T0TC=0;
	T0PC=0;
	T0PR=p-1;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}

void lcd_data(unsigned char data){
	
	IOCLR1=0xFE0000;
	IOSET1=(data&0xF0)<<16;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	ms_delay(2);
	IOCLR1=EN;
	
	IOCLR1=0xFE0000;
	IOSET1=(data&0xF)<<20;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	ms_delay(2);
	IOCLR1=EN;
	
}

void lcd_cmd(unsigned char data){
	
	IOCLR1=0xFE0000;
	IOSET1=(data&0xF0)<<16;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	ms_delay(2);
	IOCLR1=EN;
	
	IOCLR1=0xFE0000;
	IOSET1=(data&0xF)<<20;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;
	ms_delay(2);
	IOCLR1=EN;
	
}

void lcd_init(void){
	IODIR1|=0xFE0000;
	PINSEL2|=0x0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x0E);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
}

void lcd_str(char *p){
	while(*p){
		lcd_data(*p);
		p++;
	}
}





