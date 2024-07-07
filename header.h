#include<LPC21XX.H>

//========================== DELAY ==========================

void ms_delay(int ms);

//========================== LCD ==========================

#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)

void lcd_init(void);
void lcd_cmd(unsigned char data);
void lcd_data(unsigned char data);
void lcd_str(char *p);

//========================== I2C ==========================

#define SI ((I2CONSET>>3)&1)
void i2c_init(void);
void i2c_write_frame(unsigned char sa,unsigned char mr,unsigned char data);
unsigned char i2c_read_frame(unsigned char sa,unsigned char mr);

