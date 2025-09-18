/* 
 * File:   mcal_std_types.h
 * Author: Moamen Ahmed
 *
 * Created on April 21, 2025, 12:25 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/*****************include files *********************/
#include"compiler.h"
#include"STD_library.h"
#include"../MCAL/device_confg.h"

/******************** Macros *****************/
#define HIGH   0x01
#define LOW    0x00

#define ON     0x01
#define OFF    0x00

#define ACTIVE   0x01
#define IDEAL    0x00
 

#define STD_Return_TYPE   u8   // Autozar
#define E_OK    0x01
#define E_NOK   0x00

/************* ******MACRO FN ***************************/    // Only PINS 

#define SET_REG(REG_ID,BIT_POSITION)    ((REG_ID) |= ( 1<<BIT_POSITION))                      // 1 (input)
#define CLEAR_REG(REG_ID,BIT_POSITION)   ((REG_ID) &= ~( 1<<BIT_POSITION))              // 0 (output)
#define TOOGLE_REG(REG_ID,BIT_POSITION)   ((REG_ID) ^= ( 1<<BIT_POSITION))
#define READ_BIT(REG_ID,BIT_POSITION)   ((REG_ID   >>  BIT_POSITION)& 1)

/*****************UAER DATA _TYPE  *********************/

typedef unsigned char        u8;
typedef unsigned short      u16;
typedef unsigned int          u32;
typedef unsigned long       u64;

typedef signed char          s8;
typedef signed short       s16;
typedef signed int           s32;
typedef signed long        s64;

typedef float        float32;
typedef double  double64;

/****************************************************/
#endif	/* MCAL_STD_TYPES_H */

