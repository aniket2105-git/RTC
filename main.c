#include"header.h"

int main(){
	unsigned int h=0,m=0,s=0,d=0,mon=0,y=0,r,wd=0;
	char week[7][10]={"MON", "TUE", "WED", "THU", "FRI", "SAT","SUN"};
	lcd_init();
	i2c_init();
	
//*************************** TIME  ***************************
	
	i2c_write_frame(0xD0,0x2,0x71);//hr
	i2c_write_frame(0xD0,0x1,0x59);//min
	i2c_write_frame(0xD0,0x0,0x58);//sec
	
	
//*************************** DATE  ***************************
	
	i2c_write_frame(0xD0,0x4,0x07);//Date
	i2c_write_frame(0xD0,0x5,0x07);//Month
	i2c_write_frame(0xD0,0x6,0x24);//Year

//*************************** DAY  ***************************
	
	i2c_write_frame(0xD0,0x3,0x07);
	
	while(1){

		//*************************** TIME  ***************************
		
		h=i2c_read_frame(0xD0,0x2);
		m=i2c_read_frame(0xD0,0x1);
		s=i2c_read_frame(0xD0,0x0);
		r=((h>>5)&1);
		lcd_cmd(0x80);
		h&=0x1F;
		lcd_data((h/0x10)+48);
		lcd_data((h%0x10)+48);
		lcd_data(':');
		lcd_data((m/0x10)+48);
		lcd_data((m%0x10)+48);
		lcd_data(':');
		lcd_data((s/0x10)+48);
		lcd_data((s%0x10)+48);
		lcd_data(' ');
		if(r==0){
				lcd_str("AM");
			}
		else{
				lcd_str("PM");
		}
		
//*************************** DATE  ***************************	
		
		d=i2c_read_frame(0xD0,0x4);
		mon=i2c_read_frame(0xD0,0x5);
		y=i2c_read_frame(0xD0,0x6);
		lcd_cmd(0xC0);
		lcd_data((d/0x10)+48);
		lcd_data((d%0x10)+48);
		lcd_data('/');
		switch(mon){
			case 1:
				lcd_str("JAN");
				break;
			case 2:
				lcd_str("FEB");
				break;
			case 3:
				lcd_str("MAR");
				break;
			case 4:
				lcd_str("APR");
				break;
			case 5:
				lcd_str("MAY");
				break;
			case 6:
				lcd_str("JUN");
				break;
			case 7:
				lcd_str("JUL");
				break;
			case 8:
				lcd_str("AUG");
				break;
			case 9:
				lcd_str("SEPT");
				break;
			case 10:
				lcd_str("OCT");
				break;
			case 11:
				lcd_str("NOV");
				break;
			case 12:
				lcd_str("DEC");
				break;
			default:
				lcd_str("ERR!");
			break;
		}
		lcd_data('/');
		lcd_data((y/0x10)+48);
		lcd_data((y%0x10)+48);
		lcd_data(' ');
		
		
		//*************************** DAY  ***************************
		
		wd=i2c_read_frame(0xD0,0x3);
//		lcd_data((wd/0x10)+48);
//		lcd_data((wd%0x10)+48);
			switch(wd){
							case 0:
								lcd_str(week[0]);
								break;
							case 1:
								lcd_str(week[1]);
								break;
							case 2:
								lcd_str(week[2]);
								break;
							case 3:
								lcd_str(week[3]);
								break;
							case 4:
								lcd_str(week[4]);
								break;
							case 5:
								lcd_str(week[5]);
								break;
							case 7:
								lcd_str(week[6]);
								break;
			}	
		
	}
}

