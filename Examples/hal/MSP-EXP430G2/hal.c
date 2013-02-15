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
* @file     hal.c
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

//*****************************************************************************
// Include section
//*****************************************************************************

#include "dev_types.h"
#include "hal.h"

//*****************************************************************************
// Global variables 
//*****************************************************************************


//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

// function callback pointer
static void (*timer_callback_ptr) (void) = NULL;

//*****************************************************************************
// Internal function declarations
//*****************************************************************************



//*****************************************************************************
// External functions
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
void hal_init(void)
{
  // initialize both LEDs on Launchpad
  P1DIR |= (BIT0 + BIT6);
  P1OUT &= ~(BIT0 + BIT6);
}

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
void hal_toggle_led(uint8_t led)
{
  if(led == 1)
  {
    P1OUT ^= BIT0;
  }
  else if(led == 2)
  {
    P1OUT ^= BIT6;
  }
}

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
void hal_setup_timer_int(uint16_t tick_ms, void (*callback)(void))
{
  // ACLK is sourced from VLO  12 kHz
  TACCR0 = 12 * tick_ms;
  TACCTL0 = CCIE;
  TACTL = TASSEL_1 + MC_1 + TACLR;

  // save callback pointer
  timer_callback_ptr = callback;
}


//*****************************************************************************
// Internal functions
//*****************************************************************************

/**************************************************************************//**
*
* Timer_A_CCR0_ISR
*
* @brief      Timer A CCR0 ISR function
*
* @param      -
*
* @return     -
*
******************************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void)
{
  // call callback function
  timer_callback_ptr();
}
