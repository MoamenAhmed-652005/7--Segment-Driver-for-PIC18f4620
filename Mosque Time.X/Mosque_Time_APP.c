    /*
    * File:   application.c
    * Author: Moamen Ahmed
    *
    * Created on April 14, 2025, 3:11 PM
    */

    /************************ includes files*******************/
    #include "application.h"
    /**************************************************************/

    led_confg LED1 = {
        .port = GPIO_PORTC,
        .pin = GPIO_PIN0,
        .connection = ACTIVE_HIGH,
        .state = TURN_OFF,
    };


    button_confg b1 = {            // INT1
        .port = GPIO_PORTB,
        .pin = GPIO_PIN0,
        .connrction = BUTTON_ACTIVE_HIGH,
        .state = BUTTON_RELEASED,

    };

    SEG_Confg Segment_1_sec = {
        .SEG_PINS[0].port = GPIO_PORTD,
        .SEG_PINS[0].pin = GPIO_PIN0,
        .SEG_PINS[0].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[0].logic = GPIO_LOW,

        .SEG_PINS[1].port = GPIO_PORTD,
        .SEG_PINS[1].pin = GPIO_PIN1,
        .SEG_PINS[1].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[1].logic = GPIO_LOW,

        .SEG_PINS[2].port = GPIO_PORTD,
        .SEG_PINS[2].pin = GPIO_PIN2,
        .SEG_PINS[2].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[2].logic = GPIO_LOW,

        .SEG_PINS[3].port = GPIO_PORTD,
        .SEG_PINS[3].pin = GPIO_PIN3,
        .SEG_PINS[3].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[3].logic = GPIO_LOW,

        .seg_connection = SEG_CC,
    };
    SEG_Confg Segment_2_sec = {
        .SEG_PINS[0].port = GPIO_PORTD,
        .SEG_PINS[0].pin = GPIO_PIN4,
        .SEG_PINS[0].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[0].logic = GPIO_LOW,

        .SEG_PINS[1].port = GPIO_PORTD,
        .SEG_PINS[1].pin = GPIO_PIN5,
        .SEG_PINS[1].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[1].logic = GPIO_LOW,

        .SEG_PINS[2].port = GPIO_PORTD,
        .SEG_PINS[2].pin = GPIO_PIN6,
        .SEG_PINS[2].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[2].logic = GPIO_LOW,

        .SEG_PINS[3].port = GPIO_PORTD,
        .SEG_PINS[3].pin = GPIO_PIN7,
        .SEG_PINS[3].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[3].logic = GPIO_LOW,

        .seg_connection = SEG_CC,
    };
    SEG_Confg Segment_1_min = {
        .SEG_PINS[0].port = GPIO_PORTA,
        .SEG_PINS[0].pin = GPIO_PIN0,
        .SEG_PINS[0].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[0].logic = GPIO_LOW,

        .SEG_PINS[1].port = GPIO_PORTA,
        .SEG_PINS[1].pin = GPIO_PIN1,
        .SEG_PINS[1].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[1].logic = GPIO_LOW,

        .SEG_PINS[2].port = GPIO_PORTA,
        .SEG_PINS[2].pin = GPIO_PIN2,
        .SEG_PINS[2].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[2].logic = GPIO_LOW,

        .SEG_PINS[3].port = GPIO_PORTA,
        .SEG_PINS[3].pin = GPIO_PIN3,
        .SEG_PINS[3].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[3].logic = GPIO_LOW,

        .seg_connection = SEG_CC,
    };
    SEG_Confg Segment_2_min = {
        .SEG_PINS[0].port = GPIO_PORTA,
        .SEG_PINS[0].pin = GPIO_PIN4,
        .SEG_PINS[0].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[0].logic = GPIO_LOW,

        .SEG_PINS[1].port = GPIO_PORTA,
        .SEG_PINS[1].pin = GPIO_PIN5,
        .SEG_PINS[1].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[1].logic = GPIO_LOW,

        .SEG_PINS[2].port = GPIO_PORTA,
        .SEG_PINS[2].pin = GPIO_PIN6,
        .SEG_PINS[2].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[2].logic = GPIO_LOW,

        .SEG_PINS[3].port = GPIO_PORTA,
        .SEG_PINS[3].pin = GPIO_PIN7,
        .SEG_PINS[3].direction = GPIO_DIRECTION_OUTPUT,
        .SEG_PINS[3].logic = GPIO_LOW,

        .seg_connection = SEG_CC,
    };




    STD_Return_TYPE ret = E_OK; // Global Var

    u8 sec_unit = 0 ; // Counter Overflow timer
    u8 sec_tens = 0 ; 
    u8 min_unit = 0 ; 
    u8 min_tens = 0 ; 
    int device_on = 0; 


    void main(void)
    {

        ret = APP_INITIALIZE();
        
        TMR1IE =1;
        PEIE =1;
        GIE =1;
        
        TMR1 = 0;  // clear Timer 1 register
        TMR1CS =0;  //  Internal Clock
        
        // Prescalar Value
        T1CKPS0 = 1;
        T1CKPS1 = 1 ;
        
        // Timer ON
        TMR1ON = 1;
        
            // interrupt Pin INT1
                // INT Flag

            INT0IE =1 ;
            PEIE =1;
            GIE =1;    
            
                // Edge
            INTEDG0 = 0;

        
        
        while (1){

            ret = SEG_WRITE_DATA(&Segment_1_sec , sec_unit);
            ret = SEG_WRITE_DATA(&Segment_2_sec , sec_tens);
            ret = SEG_WRITE_DATA(&Segment_1_min , min_unit);
            ret = SEG_WRITE_DATA(&Segment_2_min , min_tens);
        }
    
    }

    void __interrupt() ISR(void){
        
                            
            if (TMR1IF && device_on){
            
                sec_unit ++ ;
            
                LED_TOGGLE(&LED1);
                    
                if (sec_unit == 10){
                    
                    sec_unit = 0;
                    sec_tens ++ ;
                }
                
                if (sec_tens == 6){
                    
                    sec_tens = 0 ;
                    min_unit  ++ ;
                    
                }
                if (min_unit == 6){
                    
                    min_unit = 0;
                    min_tens  ++;
                    
                }
                if (min_tens == 6){
                    
                    min_tens = 0;
                }
                
                
                
                TMR1IF = 0 ; 
                TMR1H = 0x00;     
                TMR1L = 0x00;
                
                
                
            }
            if (INT0IF) {
        
        device_on = !device_on ;
        INT0IF = 0;
    }   
        
        }
    





    STD_Return_TYPE APP_INITIALIZE(void)
    {



    ret = SEG_INTIALIZED(&Segment_1_sec);
    ret = SEG_INTIALIZED(&Segment_2_sec);
    
    ret = SEG_INTIALIZED(&Segment_1_min);
    ret = SEG_INTIALIZED(&Segment_2_min);
    
    
    ret = BUTTON_INTIALIZE(&b1);
    ret = LED_INTIALIZE (&LED1);
    
            
            
    return (ret);
    }


    void Bouncing_check(button_state btn_state, button_state *btn_vaild)
    {

    static u64 btn_unvaild_state = 0;

    if (btn_state == BUTTON_PRESSED)
    {
        btn_unvaild_state++;

        if (btn_unvaild_state > 600)
        {

        *btn_vaild = BUTTON_PRESSED;
        }
    }
    else
    {

        *btn_vaild = BUTTON_RELEASED;
        btn_unvaild_state = 0;
    }
    }