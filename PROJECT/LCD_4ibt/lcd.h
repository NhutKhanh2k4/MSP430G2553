
void PulseLcm();
void SendByte(char ByteToSend, int IsData);
void lcd_gotoxy(char Row, char Col);
void lcd_clear();
void lcd_init(void);
void lcd_puts(char *Text);
void LCD_Custom_Char(unsigned char vt, unsigned char*mgs);
void ftoa(char* string,int a,int b);
void ftoa_1(char* string, unsigned int a);
void ftoa_2(char* string, unsigned int a);
void lcd_putc(int m);
void lcd_ShiftLeft(void);
void lcd_ShiftRight(void);
void lcd_MoveRight(unsigned char n, unsigned int time);
void lcd_MoveLeft(unsigned char n, unsigned int time);
void lcd_create_char(unsigned char charCode, const unsigned char* charPattern);
void lcd_put_char(unsigned char charCode);