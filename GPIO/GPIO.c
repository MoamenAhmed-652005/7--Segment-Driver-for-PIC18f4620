/* 
 * File:   application.h
 * Author: Moamen Ahmed
 *
 * Created on April 21, 2025, 3:05 PM
 */
/*****************include files *********************/
#include "../GPIO/GPIO.h"
/****************************************************/
volatile u8 *TRIS_REG[5] = {&TRISA ,&TRISB,&TRISC,&TRISD,&TRISE};
volatile u8 *LAT_REG[5]  =  {&LATA,&LATB,&LATC,&LATD,&LATE};
volatile u8 *PORT_REG[5] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/***************functions implementation*********/ 

STD_Return_TYPE GPIO_PIN_INTIALIZED(GPIO_confg *ptr){
    
     STD_Return_TYPE RET = E_OK;
    if(NULL == ptr || ptr->port > GPIO_PORT_MAX - 1||ptr->pin > GPIO_PIN_MAX -1 )
    {
        RET = E_NOK ;
    }
    else {
       RET = GPIO_PIN_DIRECTION_INTIALIZE(ptr);
       RET = GPIO_PIN_WRITE_LOGIC (ptr, GPIO_LOW);
    }
    
  return (RET);  
}

STD_Return_TYPE GPIO_PIN_DIRECTION_INTIALIZE(GPIO_confg *ptr){
    
    STD_Return_TYPE RET = E_OK;
    if(NULL == ptr || ptr->port > GPIO_PORT_MAX - 1||ptr->pin > GPIO_PIN_MAX -1 )
    {
        RET = E_NOK ;
    }
    else {
        switch(ptr->direction){
             case GPIO_DIRECTION_OUTPUT :
                    CLEAR_REG (*TRIS_REG[ptr->port],ptr->pin);    // 0  Output
                    break;
             case  GPIO_DIRECTION_INPUT :
                     SET_REG (*TRIS_REG[ptr->port],ptr->pin);     //  1 input
                     break;
                 default :
                     RET = E_NOK ;
                   break;
        }
    }
        
    return (RET);
}

STD_Return_TYPE GPIO_PIN_GET_DIRECTION(GPIO_confg *ptr,direction_t *state){
      STD_Return_TYPE RET = E_OK;
    if(NULL == ptr || ptr->port > GPIO_PORT_MAX - 1||ptr->pin > GPIO_PIN_MAX -1||(NULL== state) )
    {
        RET = E_NOK ;
    }
    else {
        *state = READ_BIT(*TRIS_REG[ptr->port],ptr->pin);     //return status to &direction_t  member;       
    }
    
    return (RET);
}

STD_Return_TYPE GPIO_PIN_WRITE_LOGIC(GPIO_confg *ptr,logic_t log){
      STD_Return_TYPE RET = E_OK;
    if(NULL == ptr || ptr->port > GPIO_PORT_MAX - 1||ptr->pin > GPIO_PIN_MAX -1 )
    {
        RET = E_NOK ;
    }
    else {
        switch (log){
                case  GPIO_HIGH :
                    SET_REG(*LAT_REG[ptr->port],ptr->pin);
                    break;
                 case GPIO_LOW :
                       CLEAR_REG (*LAT_REG[ptr->port],ptr->pin);
                       break;
                   default :
                        RET = E_NOK;
                        break;
        }
    }
    return (RET);

}

STD_Return_TYPE GPIO_PIN_READ_LOGIC(GPIO_confg *ptr,logic_t *state){
       STD_Return_TYPE RET = E_OK;
    if(NULL == ptr || ptr->port > GPIO_PORT_MAX - 1||ptr->pin > GPIO_PIN_MAX -1 )
    {
        RET = E_NOK ;
    }
    else {
       *state = READ_BIT(*PORT_REG[ptr->port],ptr->pin); //return status to &logic_t  member;
        
    }
    
    return (RET);
}

STD_Return_TYPE GPIO_PIN_TOGGLE_LOGIC(GPIO_confg *ptr){
      
     STD_Return_TYPE RET = E_OK;
    if(NULL == ptr || ptr->port > GPIO_PORT_MAX - 1||ptr->pin > GPIO_PIN_MAX -1 )
    {
        RET = E_NOK ;
    }
    else {  
        
        TOOGLE_REG(*LAT_REG[ptr->port],ptr->pin);
    }
    
    return (RET);
}


 /*******************************************************************************/
    //  USed in &Segment 


STD_Return_TYPE GPIO_PORT_DIRECTION_INTIALIZE(port_t port,u8 dir_port){
     STD_Return_TYPE RET = E_OK;
     if(port > GPIO_PORT_MAX -1){
         RET=E_NOK ;

     }
     else {
          *TRIS_REG[port]=  dir_port ;
         
     }
         return (RET);

}

STD_Return_TYPE GPIO_PORT_GET_DIRECTION(port_t port,u8 *state){
    STD_Return_TYPE RET = E_OK;
     if(port > GPIO_PORT_MAX -1){
         RET=E_NOK ;

     }
     else {
         *state = *TRIS_REG[port];
         
     }
        return (RET);

}

STD_Return_TYPE GPIO_PORT_WRITE_LOGIC(port_t port,u8 logic){
        
     STD_Return_TYPE RET = E_OK;
     if(port > GPIO_PORT_MAX -1){
         RET=E_NOK ;

     }
     else {
         *LAT_REG[port]= logic ;
         
     }
        return (RET);

}

STD_Return_TYPE GPIO_PORT_READ_LOGIC(port_t port, u8 *state){
    
    STD_Return_TYPE RET = E_OK;
     if(port > GPIO_PORT_MAX -1){
         RET=E_NOK ;

     }
     else {
            *state = *PORT_REG[port] ; // read the logic with PORT_REG 
     }
        return (RET);

}

STD_Return_TYPE GPIO_PORT_TOGGLE_LOGIC(port_t port){
    
     STD_Return_TYPE RET = E_OK;
     if(port > GPIO_PORT_MAX -1){
         RET=E_NOK ;

     }
     else {
         *LAT_REG[port] ^= 0xFF ;
         
     }
        return (RET);

}
