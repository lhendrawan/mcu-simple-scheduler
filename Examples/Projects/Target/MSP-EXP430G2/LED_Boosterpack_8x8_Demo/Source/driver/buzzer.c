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
* @file     buzzer.c
*
* @brief    MSP430 LED Matrix Boosterpack buzzer driver source file
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

#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>
#include "buzzer.h"

//*****************************************************************************
// Global variables
//*****************************************************************************


//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************


//*****************************************************************************
// Internal function declarations
//*****************************************************************************


//*****************************************************************************
// External functions
//*****************************************************************************

/**************************************************************************//**
*
* buzzer init
*
* @brief      initialize buzzer module
*
* @param      -
*
* @return     -
*
******************************************************************************/
void buzzer_init(void)
{
  // set P1.1 as normal GPIO
  P1DIR |= BIT1;
  P1OUT &= ~(BIT1);

  // set P1.2 as TA0.1
  P1DIR |= BIT2;
  P1SEL |= BIT2;
  P1SEL2 &= ~BIT2;
}

/**************************************************************************//**
*
* buzzer_set_freq
*
* @brief      set buzzer at certain frequency
*
* @param[in]  freq_cnt    frequency counter where the buzzer to be set, if 0
*                         the buzzer is turned off
*
* @return     -
*
******************************************************************************/
void buzzer_set_freq(uint16_t freq_cnt)
{
  if(freq_cnt > 0)
  {
    // output at TA0.1 - reset/set
    TACCTL1 = OUTMOD_7;

    // start Timer A0 in up mode - duty cycle 50% at TA0.1
    TA0CCR0 = freq_cnt;
    TA0CCR1 = freq_cnt/2;
    TA0CTL = TASSEL_2 + MC_1 + TACLR;
  }
  else
  {
    // stop Timer A0
    TA0CTL = TACLR;
    TACCTL1 = 0;
  }
}

//*****************************************************************************
// Internal functions
//*****************************************************************************


