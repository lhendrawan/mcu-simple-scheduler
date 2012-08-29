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
* @file     buzzer.h
*
* @brief    driver module for buzzer on MSP430 LED Matrix Boosterpack
*
* @version  0.2.0
* 
* @author   Leo Hendrawan
*
* @remark
*
******************************************************************************/

#ifndef _BUZZER_H_
#define _BUZZER_H_

//*****************************************************************************
// Include section
//*****************************************************************************


//*****************************************************************************
// Global variable declarations
//*****************************************************************************


//*****************************************************************************
// Macros (defines) and data types
//*****************************************************************************

// data structure for buzzer play
typedef struct {
  uint16_t buzzer_freq_cnt;
  uint16_t delay;
} buzzer_tone_data_t;

#define TMR_CLK_SRC_FREQ         (1000000UL) // 1 MHz
#define TMR_TICK_PERIOD_US       (1000000UL/TMR_CLK_SRC_FREQ)

#define C3_FREQ                  (131) // (130.81)
#define C3_PERIOD_US             (1000000UL/C3_FREQ)

#define Db3_FREQ                 (139) // (138.59)
#define Db3_PERIOD_US            (1000000UL/Db3_FREQ)

#define D3_FREQ                  (147) // (146.83)
#define D3_PERIOD_US             (1000000UL/D3_FREQ)

#define Eb3_FREQ                 (156) // (155.56)
#define Eb3_PERIOD_US            (1000000UL/Eb3_FREQ)

#define E3_FREQ                  (165) // (164.81)
#define E3_PERIOD_US             (1000000UL/E3_FREQ)

#define F3_FREQ                  (175) // (174.61)
#define F3_PERIOD_US             (1000000UL/F3_FREQ)

#define Gb3_FREQ                 (185) // (185.00)
#define Gb3_PERIOD_US            (1000000UL/Gb3_FREQ)

#define G3_FREQ                  (196) // (196.00)
#define G3_PERIOD_US             (1000000UL/G3_FREQ)

#define Ab3_FREQ                 (208) // (207.65)
#define Ab3_PERIOD_US            (1000000UL/Ab3_FREQ)

#define A3_FREQ                  (220) // (220)
#define A3_PERIOD_US             (1000000UL/A3_FREQ)

#define Bb3_FREQ                 (233) // (233.08)
#define Bb3_PERIOD_US            (1000000UL/Bb3_FREQ)

#define B3_FREQ                  (247) // (246.94)
#define B3_PERIOD_US             (1000000UL/B3_FREQ)

#define C4_FREQ                  (262) // (261.63)
#define C4_PERIOD_US             (1000000UL/C4_FREQ)

#define Db4_FREQ                 (277) // (277.18)
#define Db4_PERIOD_US            (1000000UL/Db4_FREQ)

#define D4_FREQ                  (294) // (293.66)
#define D4_PERIOD_US             (1000000UL/D4_FREQ)

#define Eb4_FREQ                 (311) // (311.13)
#define Eb4_PERIOD_US            (1000000UL/Eb4_FREQ)

#define E4_FREQ                  (330) // (329.63)
#define E4_PERIOD_US             (1000000UL/E4_FREQ)

#define F4_FREQ                  (349) // (349.23)
#define F4_PERIOD_US             (1000000UL/F4_FREQ)

#define Gb4_FREQ                 (370) // (369.99)
#define Gb4_PERIOD_US            (1000000UL/Gb4_FREQ)

#define G4_FREQ                  (392) // (392.00)
#define G4_PERIOD_US             (1000000UL/G4_FREQ)

#define Ab4_FREQ                 (415) // (415.30)
#define Ab4_PERIOD_US            (1000000UL/Ab4_FREQ)

#define A4_FREQ                  (440) // (440)
#define A4_PERIOD_US             (1000000UL/A4_FREQ)

#define Bb4_FREQ                 (466) // (466.16)
#define Bb4_PERIOD_US            (1000000UL/Bb4_FREQ)

#define B4_FREQ                  (494) // (493.88)
#define B4_PERIOD_US             (1000000UL/B4_FREQ)

#define C5_FREQ                  (523) // (523.25)
#define C5_PERIOD_US             (1000000UL/C5_FREQ)

#define Db5_FREQ                 (554) // (554.37)
#define Db5_PERIOD_US            (1000000UL/Db5_FREQ)

#define D5_FREQ                  (587) // (587.33)
#define D5_PERIOD_US             (1000000UL/D5_FREQ)

#define Eb5_FREQ                 (622) // (622.25)
#define Eb5_PERIOD_US            (1000000UL/Eb5_FREQ)

#define E5_FREQ                  (659) // (659.26)
#define E5_PERIOD_US             (1000000UL/E5_FREQ)

#define F5_FREQ                  (698) // (698.46)
#define F5_PERIOD_US             (1000000UL/F5_FREQ)

#define Gb5_FREQ                 (740) // (739.99)
#define Gb5_PERIOD_US            (1000000UL/Gb5_FREQ)

#define G5_FREQ                  (784) // (783.99)
#define G5_PERIOD_US             (1000000UL/G5_FREQ)

#define Ab5_FREQ                 (831) // (830.61)
#define Ab5_PERIOD_US            (1000000UL/Ab5_FREQ)

#define A5_FREQ                  (880) // (880.00)
#define A5_PERIOD_US             (1000000UL/A5_FREQ)

#define Bb5_FREQ                 (932) // (932.33)
#define Bb5_PERIOD_US            (1000000UL/Bb5_FREQ)

#define B5_FREQ                  (988) // (987.77)
#define B5_PERIOD_US             (1000000UL/B5_FREQ)

// use the following parameters for buzzer_set_freq() function
#define PAUSE                    (0)
#define C3_TICK_CNT              (C3_PERIOD_US/TMR_TICK_PERIOD_US)
#define Db3_TICK_CNT             (Db3_PERIOD_US/TMR_TICK_PERIOD_US)
#define D3_TICK_CNT              (D3_PERIOD_US/TMR_TICK_PERIOD_US)
#define Eb3_TICK_CNT             (Eb3_PERIOD_US/TMR_TICK_PERIOD_US)
#define E3_TICK_CNT              (E3_PERIOD_US/TMR_TICK_PERIOD_US)
#define F3_TICK_CNT              (F3_PERIOD_US/TMR_TICK_PERIOD_US)
#define Gb3_TICK_CNT             (Gb3_PERIOD_US/TMR_TICK_PERIOD_US)
#define G3_TICK_CNT              (G3_PERIOD_US/TMR_TICK_PERIOD_US)
#define Ab3_TICK_CNT             (Ab3_PERIOD_US/TMR_TICK_PERIOD_US)
#define A3_TICK_CNT              (A3_PERIOD_US/TMR_TICK_PERIOD_US)
#define Bb3_TICK_CNT             (Bb3_PERIOD_US/TMR_TICK_PERIOD_US)
#define B3_TICK_CNT              (B3_PERIOD_US/TMR_TICK_PERIOD_US)
#define C4_TICK_CNT              (C4_PERIOD_US/TMR_TICK_PERIOD_US)
#define Db4_TICK_CNT             (Db4_PERIOD_US/TMR_TICK_PERIOD_US)
#define D4_TICK_CNT              (D4_PERIOD_US/TMR_TICK_PERIOD_US)
#define Eb4_TICK_CNT             (Eb4_PERIOD_US/TMR_TICK_PERIOD_US)
#define E4_TICK_CNT              (E4_PERIOD_US/TMR_TICK_PERIOD_US)
#define F4_TICK_CNT              (F4_PERIOD_US/TMR_TICK_PERIOD_US)
#define Gb4_TICK_CNT             (Gb4_PERIOD_US/TMR_TICK_PERIOD_US)
#define G4_TICK_CNT              (G4_PERIOD_US/TMR_TICK_PERIOD_US)
#define Ab4_TICK_CNT             (Ab4_PERIOD_US/TMR_TICK_PERIOD_US)
#define A4_TICK_CNT              (A4_PERIOD_US/TMR_TICK_PERIOD_US)
#define Bb4_TICK_CNT             (Bb4_PERIOD_US/TMR_TICK_PERIOD_US)
#define B4_TICK_CNT              (B4_PERIOD_US/TMR_TICK_PERIOD_US)
#define C5_TICK_CNT              (C5_PERIOD_US/TMR_TICK_PERIOD_US)
#define Db5_TICK_CNT             (Db5_PERIOD_US/TMR_TICK_PERIOD_US)
#define D5_TICK_CNT              (D5_PERIOD_US/TMR_TICK_PERIOD_US)
#define Eb5_TICK_CNT             (Eb5_PERIOD_US/TMR_TICK_PERIOD_US)
#define E5_TICK_CNT              (E5_PERIOD_US/TMR_TICK_PERIOD_US)
#define F5_TICK_CNT              (F5_PERIOD_US/TMR_TICK_PERIOD_US)
#define Gb5_TICK_CNT             (Gb5_PERIOD_US/TMR_TICK_PERIOD_US)
#define G5_TICK_CNT              (G5_PERIOD_US/TMR_TICK_PERIOD_US)
#define Ab5_TICK_CNT             (Ab5_PERIOD_US/TMR_TICK_PERIOD_US)
#define A5_TICK_CNT              (A5_PERIOD_US/TMR_TICK_PERIOD_US)
#define Bb5_TICK_CNT             (Bb5_PERIOD_US/TMR_TICK_PERIOD_US)
#define B5_TICK_CNT              (B5_PERIOD_US/TMR_TICK_PERIOD_US)


//*****************************************************************************
// External function declarations
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
void buzzer_init(void);

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
void buzzer_set_freq(uint16_t freq_cnt);

#endif /* _BUZZER_H_ */
