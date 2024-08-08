#include "msp430g2553.h"
#include "Servo.h"


/*------------------------------------------------------------------------------
Function	: Servo_Init
Purpose		: Initialize and configure servo control
Parameters	: Pin_Servo
Return		: Note
============================== FUNCTION =======================================*/
void Servo_Init(unsigned char Pin_Servo ){
  

#if TIMER_CONTROL_SERVO == TIMER0
         
        if(Pin_Servo == P1_2){
          
            P1DIR |= BIT2;
            P1SEL |= BIT2;                      // Cau hinh chan pwm
         
            TA0CCR0 = 2500;                     // Chu ki 20 ms
            TA0CCR1 = 0;                        // Ton ( 480us --> 2.6ms) : angle 0 do
            
            TA0CCTL1 = OUTMOD_7;                // Mode set/reset
            TA0CTL = TASSEL_2 | ID_3 | MC_1;    // Xung clock DCO, Chia 8, Mode up 
          
        }
        
        else if (Pin_Servo == P1_6){
          
            P1DIR |= BIT6;
            P1SEL |= BIT6;                     // Cau hinh chan pwm
         
            TA0CCR0 = 2500;                   // Chu ki 20 ms
            TA0CCR1 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
            
            TA0CCTL1 = OUTMOD_7;              // Mode set/reset
            TA0CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
        }
        
        else if (Pin_Servo == P1_2_6){
          
            P1DIR |= BIT2 + BIT6;
            P1SEL |= BIT2 + BIT6;             // Cau hinh chan pwm
         
            TA0CCR0 = 2500;                   // Chu ki 20 ms
            TA0CCR1 = 0;                     // Ton ( 480us --> 2.6ms) : angle 0 do
            
            TA0CCTL1 = OUTMOD_7;              // Mode set/reset
            TA0CTL = TASSEL_2 | ID_3 | MC_1; // Xung clock DCO, Chia 8, Mode up 
        }

      
#elif TIMER_CONTROL_SERVO == TIMER1
        
          if(Pin_Servo == P2_1){
            
              P2DIR |= BIT1;
              P2SEL |= BIT1;                    // Cau hinh chan pwm
           
              TA1CCR0 = 2500;                   // Chu ki 20 ms
              TA1CCR1 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
              
              TA1CCTL1 = OUTMOD_7;              // Mode set/reset
              TA1CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
            
          }
          
          else if (Pin_Servo == P2_2){
              P2DIR |=  BIT2;
              P2SEL |=  BIT2;                   // Cau hinh chan pwm
           
              TA1CCR0 = 2500;                   // Chu ki 20 ms
              TA1CCR1 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
              
              TA1CCTL1 = OUTMOD_7;              // Mode set/reset
              TA1CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
            
            
          }
          
          else if (Pin_Servo == P2_1_2){
            
              P2DIR |= BIT1 + BIT2;
              P2SEL |= BIT1 + BIT2;             // Cau hinh chan pwm
           
              TA1CCR0 = 2500;                   // Chu ki 20 ms
              TA1CCR1 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
              
              TA1CCTL1 = OUTMOD_7;              // Mode set/reset
              TA1CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
   
          }
          
          else if (Pin_Servo == P2_4){
            
              P2DIR |= BIT4;
              P2SEL |= BIT4;                    // Cau hinh chan pwm
           
              TA1CCR0 = 2500;                   // Chu ki 20 ms
              TA1CCR2 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
              
              TA1CCTL2 = OUTMOD_7;              // Mode set/reset
              TA1CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
            
            
          }
          
          else if (Pin_Servo == P2_5){
            
              P2DIR |= BIT5;
              P2SEL |= BIT5;                    // Cau hinh chan pwm
           
              TA1CCR0 = 2500;                   // Chu ki 20 ms
              TA1CCR2 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
              
              TA1CCTL2 = OUTMOD_7;              // Mode set/reset
              TA1CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
            
          }
          
          else if (Pin_Servo == P2_4_5){
              
              P2DIR |= BIT4 + BIT5;
              P2SEL |= BIT4 + BIT5;             // Cau hinh chan pwm
           
              TA1CCR0 = 2500;                   // Chu ki 20 ms
              TA1CCR2 = 0;                      // Ton ( 480us --> 2.6ms) : angle 0 do
              
              TA1CCTL2 = OUTMOD_7;              // Mode set/reset
              TA1CTL = TASSEL_2 | ID_3 | MC_1;  // Xung clock DCO, Chia 8, Mode up 
            
            
          }
 
 #endif 
}
/*=========================== END - FUNCTION ====================================*/


/*------------------------------------------------------------------------------
Function	: Servo_Angle
Purpose		: Set angle Servo
Parameters	: Pin_Servo, angle
Return		: Note
============================== FUNCTION =======================================*/
void Servo_Angle(unsigned char Pin_Servo, unsigned char angle){
  
/* 
  TA1CCR1 = 60  : 48 us  ==> angle: 0
  ...
  TA1CCR1 = 192  : 1.5 ms  ==> angle: 90
  ...
  TA1CCR1 = 325  : 2.6 ms  ==> angle: 180
 
*/

  unsigned int reg = map(angle, 0, 180, 60, 325);
  
  
#if TIMER_CONTROL_SERVO == TIMER0
  
    TA0CCR1 = reg;                     

#elif TIMER_CONTROL_SERVO == TIMER1
  
    if( Pin_Servo == P2_1 || Pin_Servo == P2_2 || Pin_Servo == P2_1_2) TA1CCR1 = reg;
      
    else if (Pin_Servo == P2_4 || Pin_Servo == P2_5 || Pin_Servo == P2_4_5) TA1CCR2 = reg;

#endif 
  
}
/*=========================== END - FUNCTION ====================================*/

/*------------------------------------------------------------------------------
Function	: map
Purpose		: Init and configure for Modul UART
Parameters	: x, input_min, input_max,output_min, output_max
Return		: Note
============================== FUNCTION =======================================*/
long map(long x, long input_min, long input_max, long output_min, long output_max) {
    return (x - input_min) * (output_max - output_min) / (input_max - input_min) + output_min;
}
/*=========================== END - FUNCTION ====================================*/

  