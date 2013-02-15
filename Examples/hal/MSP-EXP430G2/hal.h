/******************************************************************************
* Copyright (c) 2012-2013, Leo Hendrawan
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the MSS PROJECT nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE MSS PROJECT OR ITS
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**************************************************************************//**
* 
* @file     hal.h
* 
* @brief    hardware abstraction layer (hal) module for MSS demo on
*           MSP-EXP430G2 Launchpad board
* 
* @version  0.2.1
*
* @author   Leo Hendrawan
* 
* @remark   
* 
******************************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

//*****************************************************************************
// Include section
//*****************************************************************************

#include "dev_types.h"

//*****************************************************************************
// Global variable declarations 
//*****************************************************************************


//*****************************************************************************
// Macros (defines) and data types 
//*****************************************************************************

// red LED on MSP-EXP430G2 Launchpad
#define HAL_LED1_ON()            do {P1OUT |= BIT0;} while(0)
#define HAL_LED1_OFF()           do {P1OUT &= ~BIT0;} while(0)
#define HAL_LED1_TOGGLE()        hal_toggle_led(1)

// green LED on MSP-EXP430G2 Launchpad
#define HAL_LED2_ON()            do {P1OUT |= BIT6;} while(0)
#define HAL_LED2_OFF()           do {P1OUT &= ~BIT6;} while(0)
#define HAL_LED2_TOGGLE()        hal_toggle_led(2)

// delay loop - shall not release scheduler
#define HAL_DELAY_LOOP_1S()      do {__delay_cycles(4000000);} while(0);

#define HAL_ASSERT(x)            if(!(x)) do{__disable_interrupt(); \
	                                         while(1);} while(0)

//*****************************************************************************
// External function declarations
//*****************************************************************************

/**************************************************************************//**
*
* hal_init
*
* @brief      initialize the hal module
*
* @param      -
*
* @return     -
*
******************************************************************************/
void hal_init(void);

/**************************************************************************//**
*
* hal_toggle_led
*
* @brief      toggle a LED
*
* @param[in]  led   LED number to be toggled
*
* @return     -
*
******************************************************************************/
void hal_toggle_led(uint8_t led);

/**************************************************************************//**
*
* hal_setup_timer_int
*
* @brief      setup a timer interrupt
*
* @param[in]  tick_ms     timer interrupt tick in miliseconds
* @param[in]  callback    callback function to be called every timer tick
*
* @return     -
*
******************************************************************************/
void hal_setup_timer_int(uint16_t tick_ms, void (*callback)(void));


#endif /* _HAL_H_ */

