#include "msp430g2553.h"
#include "DHT11.h"




/*--------------------------------------------------------------------------------
Function	: DHT11_Start
Purpose		: Send interface start signal to DHT11
Parameters	: None
Return		: Note
Note            : Do not use in main.c
============================== FUNCTION =======================================*/
void DHT11_Start(){
    MCU_DIR_OUTPUT();                   
    MCU_OUT_HIGH();                     
    __delay_cycles(60);
    MCU_OUT_LOW();                      
    __delay_cycles(18000);
    MCU_OUT_HIGH();                     
    MCU_DIR_INPUT();                    
    __delay_cycles(35);                 
 }
/*=========================== END - FUNCTION ====================================*/





/*--------------------------------------------------------------------------------
Function	: waiting_for_response
Purpose		: Wait for a response signal from DHT11
Parameters	: None
Return		: TRUE or FALSE
Note            : Do not use in main.c
============================== FUNCTION =======================================*/
unsigned char waiting_for_response(){
  
  unsigned int timeOut = 0; // Bien chong lap vo han
  timeOut = 0;
  if(MCU_INPUT())
    return 0;
  else
    while(!MCU_INPUT()){ // doi signal len 1
      if(++timeOut >1000)
        return 0;
    }
  
  __delay_cycles(60);
  
  timeOut = 0;
  if(!MCU_INPUT())
    return 0;
  else
    while(MCU_INPUT()){ //doi signal xuong 0
      if(++timeOut >1000)
        return 0;
    } 
  
  return 1;
}
/*=========================== END - FUNCTION ====================================*/




/*--------------------------------------------------------------------------------
Function	: DHT11_Read
Purpose		: Send interface start signal to DHT11
Parameters	: variable address temperature and humidity
Return		: TRUE or FALSE ( do not used)
============================== FUNCTION =======================================*/
unsigned char DHT11_Read(unsigned char *temperature, unsigned char *humidity){
  
  unsigned int timeOut = 0;
  unsigned char check_sum, buffer[5] = {0,0,0,0,0};
  
  DHT11_Start();
  if (!waiting_for_response()) return 0;
  
  for(unsigned char i = 0; i < 5; i++){         // read 5 byte data from DHT11
    for(unsigned char j = 0; j < 8; j++){
      timeOut = 0;
      while(!MCU_INPUT()){ // doi len 1
        if(++timeOut >1000)
          return 0;
      }
      
      __delay_cycles(28);
      
      timeOut = 0;
      if(MCU_INPUT()){
        buffer[i]|= (1<<(7-j));
        while(MCU_INPUT()){
          if(++timeOut >1000)
            return 0;
        }
      }
    }
  }
  
  MCU_DIR_OUTPUT ();
  MCU_OUT_HIGH();
  
  *humidity = buffer[0];
  *temperature = buffer[2];
  check_sum = *temperature + *humidity;
 
  if(check_sum != buffer[4])
    return 0;
  
  return 1;
}
/*=========================== END - FUNCTION ====================================*/


