
#include "msp430g2553.h"
#include "lcd.h"
#include <string.h>
#include <stdio.h>

unsigned char do_C[] = {
    0x1E,
    0x12,
    0x12,
    0x1E,
    0x00,
    0x00,
    0x00,
    0x00
};


void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  
  //Tat dao dong ngoai o chan P2.6 va P2.7 de su dung chan GPIO cho LCD
  P2SEL &=~ (BIT6 + BIT7); 
  
  lcd_init();//khoi tao lcd
  lcd_clear();//claer mang hinh lcd
  char buffer[3];
  float f = 3.14 ;
  lcd_create_char(0, do_C);
  
  while (1)
  {
      lcd_gotoxy(0,3);
      lcd_puts("NHUT KHANH");
      lcd_gotoxy(1,0);
      sprintf(buffer, "%.2f", f);
      //ftoa(buffer,3,14);
      lcd_puts(buffer);
      lcd_gotoxy(1,15);
      lcd_put_char(0);
    
  }
  

}
