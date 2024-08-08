
#include "msp430g2553.h"

#define LCM_DIR P2DIR
#define LCM_OUT P2OUT

#define LCM_PIN_RS BIT2
#define LCM_PIN_EN BIT3
#define LCM_PIN_D7 BIT7
#define LCM_PIN_D6 BIT6
#define LCM_PIN_D5 BIT5
#define LCM_PIN_D4 BIT4

#define LCM_PIN_MASK ((LCM_PIN_RS|LCM_PIN_EN|LCM_PIN_D7|LCM_PIN_D6|LCM_PIN_D5|LCM_PIN_D4))
#define FALSE 0
#define TRUE 1

//xung chot tai chan E
void PulseLcm(){
	LCM_OUT &=~ LCM_PIN_EN;
	__delay_cycles(200);
	LCM_OUT |=LCM_PIN_EN;
	__delay_cycles(200);
	LCM_OUT &=~LCM_PIN_EN;
	__delay_cycles(200);
}

//ham xuat 1 byte
void SendByte(char ByteToSend, int IsData)
{
	LCM_OUT &=(~LCM_PIN_MASK);
	LCM_OUT |=(ByteToSend & 0xF0); //1111 0000
	if(IsData == TRUE)
		LCM_OUT |= LCM_PIN_RS; //neu gui du lieu thi RS=1
	else
		LCM_OUT &=~ LCM_PIN_RS; //neu ghi lenh thi RS=0
	PulseLcm();	//chot
	LCM_OUT &=(~LCM_PIN_MASK);
	LCM_OUT |=((ByteToSend & 0x0F)<<4);
	if(IsData == TRUE)
		LCM_OUT |= LCM_PIN_RS;
	else
		LCM_OUT &=~ LCM_PIN_RS;
	PulseLcm();	
}

//ham dat vi tri con tro
void lcd_gotoxy(char Row, char Col)
{
	char address;
	if(Row==0)
          address=0;
	else
          address=0x40;
        address |= Col; //ad+=col
	SendByte(0x80|address,FALSE);
}

//ham xoa mang hinh LCD
void lcd_clear()
{
	SendByte(0x01,FALSE);
	SendByte(0x02,FALSE);
}

//ham khoi tao LCD
void lcd_init(void)
{
	LCM_DIR |=LCM_PIN_MASK;
	LCM_OUT &=(~LCM_PIN_MASK);
	__delay_cycles(100000);
	LCM_OUT &=~ LCM_PIN_RS;
	LCM_OUT &=~ LCM_PIN_EN;
	LCM_OUT = 0x20; //
	PulseLcm();
	SendByte(0x28, FALSE);
	SendByte(0x0E, FALSE);
	SendByte(0x06, FALSE);
	SendByte(0x0C, FALSE);
}

// CGRAM
void LCD_Custom_Char(unsigned char vt, unsigned char*mgs){
  if(vt<8){
    SendByte(0x40 + (vt*8),FALSE);
    for(char i=0; i<8; i++){
        SendByte(mgs[i], TRUE);
    }
  }
}

//xuat 1 chuoi ky tu tai vi tri con tro
void lcd_puts(char *Text)
{
    char *c;
    c = Text;
    while ((c!=0) && (*c!=0))
    {
        SendByte(*c,TRUE);
        c++;
    }
}

void lcd_putc(int m){
  if(m<8)
    SendByte(m, TRUE);
}


void lcd_ShiftLeft(void){
    SendByte(0x18,FALSE);
}

void lcd_ShiftRight(void){
    SendByte(0x1C,FALSE);
}

void lcd_MoveRight(unsigned char n, unsigned int time)
{
    unsigned int i, j;
    for(i = 0; i < n; i++){
      lcd_ShiftRight();
      for(j = 0 ; j < time ; j++){
        __delay_cycles(1000); // delay 1ms
      }
    }
}

void lcd_MoveLeft(unsigned char n, unsigned int time)
{
    unsigned int i, j;
    for(i = 0; i < n; i++){
      lcd_ShiftLeft();
      for(j = 0 ; j < time ; j++){
        __delay_cycles(1000); // delay 1ms
      }
    }
}

// ***************************************************
// Ten CTC:          lcd_create_char 
// Thong so dau vao:    DIA CHI BO NHO CGRAM, MANG KI TU DAT BIET       
// Thong so dau ra:     
// Cong dung:        // TAO VÀ LUU KI TU DAT BIET VAO BO NHO CGRAM  
// ***************************************************
void lcd_create_char(unsigned char charCode, const unsigned char* charPattern){
    unsigned char charAddr = charCode * 8; // DIA CHO BAT DAU BO NHO CGRAM CHO KI TU DAT BIET
    SendByte(0x40 | (charAddr & 0x3F), FALSE);
    for (int i = 0; i < 8; i++) { // GUI DU LIEU CHUA KI T? DAT BIET
        SendByte(charPattern[i], TRUE);
    }
}

// ***************************************************
// Ten CTC:          lcd_put_char 
// Thong so dau vao:    MANG KI TU DAT BIET       
// Thong so dau ra:     
// Cong dung:        // HIEN THI KI TU DAT BIET LEN LCD
// ***************************************************
void lcd_put_char(unsigned char charCode){
    SendByte(charCode, TRUE);
}




//bien doi 1 so thuc sang chuoi de hien thi len LCD
void ftoa(char* string,int a,int b)
{
    string[0]=a/1000+0X30; //ngan // 0X30=48 THAP PHAN
    string[1]=(a%1000)/100+48; // tram
    string[2]=((a%1000)%100)/10+48; //chuc
    string[3]=((a%1000)%100)%10+48; //donvi
    if(b!=0)
    string[4]=44;
    string[5]=b/1000+0X30;//ngan // 0X30=48 THAP PHAN
    string[6]=(b%1000)/100+48; // tram
    string[7]=((b%1000)%100)/10+48; // chuc
    string[8]=((b%1000)%100)%10+48; // donvi
}

void ftoa_1(char* string, unsigned int a)
{
    string[0]=((a%1000)%100)/10+48; //chuc
    string[1]=((a%1000)%100)%10+48; //donvi
}

void ftoa_2(char* string, unsigned int a)
{
    string[0]=((a%1000)%100)%10+48; //donvi
}

