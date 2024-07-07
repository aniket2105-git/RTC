#include"header.h"

void i2c_init(void){
	PINSEL0|=0x50;
	I2SCLL=75;
	I2SCLH=75;
	I2CONSET=(1<<6);
}

void i2c_write_frame(unsigned char sa,unsigned char mr,unsigned char data){

	//*************************** START  ***************************
	
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);
//	if(I2STAT!=0x8){
//		goto exit;
//	}
	
	//*************************** SLAVE ADDRESS ***************************
	
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x20){
		goto exit;
	}
	
	//*************************** MEM ADDRESS ***************************
	
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x30){
		goto exit;
	}
	
	//*************************** DATA  ***************************
	
	I2DAT=data;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x30){
		goto exit;
	}
	
		
//*************************** EXIT  ***************************
	
	exit:
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
}







unsigned char i2c_read_frame(unsigned char sa,unsigned char mr){
	
//*************************** START  ***************************
	unsigned char res;
	I2CONSET=(1<<5);
	I2CONCLR=(1<<3);
	while(SI==0);
	I2CONCLR=(1<<5);
//	if(I2STAT!=0x8){
//		goto exit;
//	}
		
//*************************** SLAVE ADDRESS  ***************************
	
	I2DAT=sa;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x20){
		goto exit;
	}
	
//*************************** MEM ADDRESS  ***************************
	
	I2DAT=mr;
	I2CONCLR=(1<<3);
	while(SI==0);
	if(I2STAT==0x30){
		goto exit;
	}
	
//*************************** RESET  ***************************
			
			I2CONSET=(1<<5);
			I2CONCLR=(1<<3);
			while(SI==0);
			I2CONCLR=(1<<5);
//			if(I2STAT!=0x10){
//				goto exit;
//			}
			
//*************************** SLAVE ADDRESS  ***************************
			
			I2DAT=sa|1;
			I2CONCLR=(1<<3);
			while(SI==0);
			if(I2STAT==0x48){
				goto exit;				
			}
			
//*************************** DATA  ***************************
			I2CONCLR=(1<<3);
			while(SI==0);
			res=I2DAT;
			if(I2STAT==0x30){
					goto exit;
			}

//*************************** EXIT  ***************************
	exit:
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
	return res;
	
}



