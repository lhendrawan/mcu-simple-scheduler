/******************************************************************************
* Copyright (c) 2012, Leo Hendrawan
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
* @file     demo_cfg.h
* 
* @brief    MSP430 Launchpad LED Boosterpack Cascade MSS demo configuration
*           header file
* 
* @version  0.2.1
* 
* @author   Leo Hendrawan
*
* @remark
* 
******************************************************************************/

#ifndef _DEMO_CFG_H_
#define _DEMO_CFG_H_

//*****************************************************************************
// Include section
//*****************************************************************************


//*****************************************************************************
// Global variable declarations 
//*****************************************************************************


//*****************************************************************************
// Macros (defines) and data types 
//*****************************************************************************

// running text shift period ini milliseconds
#define RUNNING_TEXT_MOV_PERIOD_MAX_MS  (300)
#define RUNNING_TEXT_MOV_PERIOD_MIN_MS  (25)
#define RUNNING_TEXT_MOV_PERIOD_STEP_MS (25)

// number of 8x8 cascade LED matrixes
#define NUM_OF_LED_MATRIXES             (11)

// moving text display data - see led_matrix.h for character definitions
#define RUNNING_TEXT_DATA  \
{                        \
  LED_MATRIX_TI_LOGO,    \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_M,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_S,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_S,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_R,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_U,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_N,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_N,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_I,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_N,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_G,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_O,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_N,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_T,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_I,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_M,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_S,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_P,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_4,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_3,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_0,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_G,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_2,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_X,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_X,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_V,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_A,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_L,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_U,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_E,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_L,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_I,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_N,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_E,     \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_TI_LOGO,    \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK, \
  LED_MATRIX_CHAR_BLANK \
}

// buzzer tone data - see buzzer.h for buzzer tone definitions
#define BUZZER_TONE_DATA  \
{                         \
    {A3_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {A3_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {A3_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {F3_TICK_CNT,  375},  \
    {C4_TICK_CNT,  125},  \
    {A3_TICK_CNT,  500},  \
    {F3_TICK_CNT,  375},  \
    {C4_TICK_CNT,  125},  \
    {A3_TICK_CNT,  1000}, \
    {E4_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {E4_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {E4_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {F4_TICK_CNT,  375},  \
    {C4_TICK_CNT,  125},  \
    {Ab3_TICK_CNT, 500},  \
    {F3_TICK_CNT,  375},  \
    {C4_TICK_CNT,  125},  \
    {A3_TICK_CNT,  1000}, \
    {A4_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {A3_TICK_CNT,  350},  \
    {PAUSE,        25},   \
    {A3_TICK_CNT,  125},  \
    {A4_TICK_CNT,  475},  \
    {PAUSE,        25},   \
    {Ab4_TICK_CNT, 375},  \
    {G4_TICK_CNT,  125},  \
    {Gb4_TICK_CNT, 85},   \
    {F4_TICK_CNT,  85},   \
    {Gb4_TICK_CNT, 85},   \
    {PAUSE,        250},  \
    {Bb3_TICK_CNT, 250},  \
    {Eb4_TICK_CNT, 500},  \
    {D4_TICK_CNT,  375},  \
    {Db4_TICK_CNT, 125},  \
    {C4_TICK_CNT,  85},   \
    {B3_TICK_CNT,  85},   \
    {C4_TICK_CNT,  85},   \
    {PAUSE,        250},  \
    {F3_TICK_CNT,  250},  \
    {Ab3_TICK_CNT, 500},  \
    {F3_TICK_CNT,  375},  \
    {C4_TICK_CNT,  125},  \
    {A3_TICK_CNT,  500},  \
    {F3_TICK_CNT,  375},  \
    {C4_TICK_CNT,  125},  \
    {A3_TICK_CNT,  1000}, \
    {PAUSE,        2000}, \
  }



//*****************************************************************************
// External function declarations
//*****************************************************************************


#endif /* _DEMO_CFG_H_*/
