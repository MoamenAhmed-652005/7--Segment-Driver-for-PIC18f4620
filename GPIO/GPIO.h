/*
 * File:   GPIO.h
 * Author: Moamen Ahmed
 *
 * Created on April 21, 2025, 12:33 AM
 */

#ifndef GPIO_H
#define GPIO_H
/************************ includes files*******************/
#include "../mcal_std_types.h"
// #include "pic18f4620.h"

/*****************MACROS****************************/
#define GPIO_PORT_MAX 5
#define GPIO_PIN_MAX 8

/*****************UAER DATA _TYPE  *********************/
typedef enum
{
    GPIO_PORTA = 0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE
} port_t;
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
} pin_t;

typedef enum
{ // for TRIS_REG
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT

} direction_t;

typedef enum
{ // for LAT_REG
    GPIO_LOW = 0,
    GPIO_HIGH
} logic_t;
typedef struct
{
    u8 port : 3; // Bit field
    u8 pin : 3;
    u8 direction : 1;
    u8 logic : 1;
} GPIO_confg;

/****************Function Prototype***************************/

STD_Return_TYPE GPIO_PIN_INTIALIZED(GPIO_confg *ptr);          // LAT off
STD_Return_TYPE GPIO_PIN_DIRECTION_INTIALIZE(GPIO_confg *ptr); // determine the IN/OUT put
STD_Return_TYPE GPIO_PIN_GET_DIRECTION(GPIO_confg *ptr, direction_t *state);
STD_Return_TYPE GPIO_PIN_WRITE_LOGIC(GPIO_confg *ptr, logic_t log);
STD_Return_TYPE GPIO_PIN_READ_LOGIC(GPIO_confg *ptr, logic_t *state);
STD_Return_TYPE GPIO_PIN_TOGGLE_LOGIC(GPIO_confg *ptr);

/****************************/

STD_Return_TYPE GPIO_PORT_DIRECTION_INTIALIZE(port_t port, u8 dir_port);
STD_Return_TYPE GPIO_PORT_GET_DIRECTION(port_t port, u8 *state);
STD_Return_TYPE GPIO_PORT_WRITE_LOGIC(port_t port, u8 logic);
STD_Return_TYPE GPIO_PORT_READ_LOGIC(port_t port, u8 *state);
STD_Return_TYPE GPIO_PORT_TOGGLE_LOGIC(port_t port);

/************************************************************/
#endif /* GPIO_H */
