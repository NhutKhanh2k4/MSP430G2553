#include "msp430g2553.h"
#include "ADC.h"

/*--------------------------------------------------------------------------------
Function	: ADC_Init
Purpose		: Init and configure for Modul ADC
Parameters	: Channel Input ADC
Return		: Note
============================== FUNCTION =======================================*/
void ADC_Init(unsigned char channel)  // Single-Channel Mode
{
    ADC10CTL0 = SREF_0 + ADC10ON + ADC10SHT_3 + MSC; // Cau hình ADC: chon dien áp tham chieu ( Vcc, Vss) + bat ADC + Tg lay mau (64 clock cycles)
    ADC10CTL1 = ADC10DIV_0 + ADC10SSEL_0;   // Bo chia = 0 + su dung clock source ADC10OSC (5MHz)

    /* Setup Channel ADC */
    switch(channel){
        
      case CHANNEL_A0:{ 
            ADC10CTL1 |= INCH_0;         // Chon kênh A0 lam input ADC
            ADC10AE0  |= BIT0;          // Cho phép dau vào analog trên chân A0
      }break;
    
      case CHANNEL_A1:{
              ADC10CTL1 |= INCH_1; 
              ADC10AE0  |= BIT1;
        }break;
        
      case CHANNEL_A2:{
                ADC10CTL1 |= INCH_2;
                ADC10AE0  |= BIT2;
          }break;
          
      case CHANNEL_A3:{
                ADC10CTL1 |= INCH_3; 
                ADC10AE0  |= BIT3;
          }break;
          
      case CHANNEL_A4:{
                ADC10CTL1 |= INCH_4; 
                ADC10AE0  |= BIT4;
          }break;
          
      case CHANNEL_A5:{
                ADC10CTL1 |= INCH_5; 
                ADC10AE0  |= BIT5;
          }break;
          
      case CHANNEL_A6:{
                ADC10CTL1 |= INCH_6; 
                ADC10AE0  |= BIT6;
          }break;
          
      case CHANNEL_A7:{
                ADC10CTL1 |= INCH_7; 
                ADC10AE0  |= BIT7;
          }break;
    }

}
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: ADC_Get_Value
Purpose		: Get value ADC
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
unsigned int ADC_Get_Value(void)
{
    ADC10CTL0 |= ENC + ADC10SC;     // Start ADC conversion
    while (ADC10CTL1 & ADC10BUSY);  // Wait for the conversion to complete
    return ADC10MEM;                // retuen ADC value
}
/*=========================== END - FUNCTION ====================================*/




/*--------------------------------------------------------------------------------
Function	: ADC_Init_Mode
Purpose		: Init and configure for Modul ADC with other Mode
Parameters	: Channel Input ADC
Return		: Note
============================== FUNCTION =======================================*/
void ADC_Init_Mode3(unsigned char channel)      // Repeat-Single-Channel Mode
{   
  
    ADC10CTL0 = SREF_0 + ADC10ON + ADC10SHT_3 + MSC; // Cau hình ADC
    ADC10CTL1 = CONSEQ_2 + ADC10DIV_0 + ADC10SSEL_0; // Cho do repeat-single-channel, kênh A5
      
    /* Setup Channel ADC */
    switch(channel){
        
      case CHANNEL_A0:{ 
            ADC10CTL1 |= INCH_0;         // Chon kênh A0 lam input ADC
            ADC10AE0  |= BIT0;          // Cho phép dau vào analog trên chân A0
      }break;
    
      case CHANNEL_A1:{
              ADC10CTL1 |= INCH_1; 
              ADC10AE0  |= BIT1;
        }break;
        
      case CHANNEL_A2:{
                ADC10CTL1 |= INCH_2;
                ADC10AE0  |= BIT2;
          }break;
          
      case CHANNEL_A3:{
                ADC10CTL1 |= INCH_3; 
                ADC10AE0  |= BIT3;
          }break;
          
      case CHANNEL_A4:{
                ADC10CTL1 |= INCH_4; 
                ADC10AE0  |= BIT4;
          }break;
          
      case CHANNEL_A5:{
                ADC10CTL1 |= INCH_5; 
                ADC10AE0  |= BIT5;
          }break;
          
      case CHANNEL_A6:{
                ADC10CTL1 |= INCH_6; 
                ADC10AE0  |= BIT6;
          }break;
          
      case CHANNEL_A7:{
                ADC10CTL1 |= INCH_7; 
                ADC10AE0  |= BIT7;
          }break;
    }

}

void ADC_Init_Mode2(unsigned char end_channel)                  //Sequence-of-Channels Mode
{  
    ADC10CTL0 = SREF_0 + ADC10ON + ADC10SHT_3 + MSC;            // Cau hình ADC
    ADC10CTL1 = CONSEQ_1 + ADC10DIV_0 + ADC10SSEL_0;            // ho do sequence-of-channels, kênh cuoi cùng là end_channel
                                                                // CCho phép dau vào analog trên các chân A0, A1 ->...end_channel
    
    /* Setup Channel ADC */
    switch(end_channel){
        
      case CHANNEL_A0:{ 
            ADC10CTL1 |= INCH_0;         // Chon kênh A0 lam input ADC
            ADC10AE0  |= BIT0;          // Cho phép dau vào analog trên chân A0
      }break;
    
      case CHANNEL_A1:{
              ADC10CTL1 |= INCH_1; 
              ADC10AE0  |= (BIT0 + BIT1);
        }break;
        
      case CHANNEL_A2:{
                ADC10CTL1 |= INCH_2;
                ADC10AE0  |= (BIT0 + BIT1 + BIT2);
          }break;
          
      case CHANNEL_A3:{
                ADC10CTL1 |= INCH_3; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3);
          }break;
          
      case CHANNEL_A4:{
                ADC10CTL1 |= INCH_4; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4);
          }break;
          
      case CHANNEL_A5:{
                ADC10CTL1 |= INCH_5; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
          }break;
          
      case CHANNEL_A6:{
                ADC10CTL1 |= INCH_6; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
          }break;
          
      case CHANNEL_A7:{
                ADC10CTL1 |= INCH_7; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
          }break;
    }
  
  
}

void ADC_Init_Mode4(unsigned char end_channel)                  //Repeat-Sequence-of-Channels Mode
{  
    ADC10CTL0 = SREF_0 + ADC10ON + ADC10SHT_3 + MSC;            // Cau hình ADC
    ADC10CTL1 = CONSEQ_3 + ADC10DIV_0 + ADC10SSEL_0;            // Cho do sequence-of-channels, kênh cuoi cùng là end_channel
                                                                // Cho phép dau vào analog trên các chân A0, A1 ->...end_channel
    
    /* Setup Channel ADC */
    switch(end_channel){
        
      case CHANNEL_A0:{ 
            ADC10CTL1 |= INCH_0;         // Chon kênh A0 lam input ADC
            ADC10AE0  |= BIT0;          // Cho phép dau vào analog trên chân A0
      }break;
    
      case CHANNEL_A1:{
              ADC10CTL1 |= INCH_1; 
              ADC10AE0  |= (BIT0 + BIT1);
        }break;
        
      case CHANNEL_A2:{
                ADC10CTL1 |= INCH_2;
                ADC10AE0  |= (BIT0 + BIT1 + BIT2);
          }break;
          
      case CHANNEL_A3:{
                ADC10CTL1 |= INCH_3; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3);
          }break;
          
      case CHANNEL_A4:{
                ADC10CTL1 |= INCH_4; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4);
          }break;
          
      case CHANNEL_A5:{
                ADC10CTL1 |= INCH_5; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5);
          }break;
          
      case CHANNEL_A6:{
                ADC10CTL1 |= INCH_6; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
          }break;
          
      case CHANNEL_A7:{
                ADC10CTL1 |= INCH_7; 
                ADC10AE0  |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
          }break;
    }
  
  
}

/*=========================== END - FUNCTION ====================================*/






/*--------------------------------------------------------------------------------
Function	: Start_ADC_Mode
Purpose		: Start converting ADC
Parameters	: Channel Input ADC
Return		: Note
============================== FUNCTION =======================================*/
void Start_ADC_Mode2(void) {
    ADC10CTL0 |= ENC + ADC10SC; // Bat dau quá trình chuyen doi ADC
    while (ADC10CTL1 & ADC10BUSY); // Ðoi cho quá trình chuyen doi hoàn thành
}
void Start_ADC_Mode3(void) {
    ADC10CTL0 |= ENC + ADC10SC; 
}
void Start_ADC_Mode4(void) {
    ADC10CTL0 |= ENC + ADC10SC; 
}
/*=========================== END - FUNCTION ====================================*/


/*--------------------------------------------------------------------------------
Function	: ADC_Get_Value_Mode
Purpose		: Get value ADC
Parameters	: None
Return		: Note
============================== FUNCTION =======================================*/
unsigned int ADC_Get_Value_Mode2(void) {
    return ADC10MEM;
}

unsigned int ADC_Get_Value_Mode3(void) {
    while (ADC10CTL1 & ADC10BUSY); 
    return ADC10MEM; 
}

unsigned int ADC_Get_Value_Mode4(void) {
    while (ADC10CTL1 & ADC10BUSY); 
    return ADC10MEM; 
}

/*=========================== END - FUNCTION ====================================*/
