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
* @file     led_matrix.h
*
* @brief    MSP430 LED Matrix Boosterpack LED Matrix driver header file
*
* @version  0.2.1
* 
* @author   Leo Hendrawan
*
* @remark
*
******************************************************************************/

#ifndef _LED_MATRIX_H_
#define _LED_MATRIX_H_

//*****************************************************************************
// Include section
//*****************************************************************************


//*****************************************************************************
// Global variable declarations
//*****************************************************************************


//*****************************************************************************
// Macros (defines) and data types
//*****************************************************************************

// characters
#define LED_MATRIX_TI_LOGO       0x08, 0x38, 0x1F, 0x3F, 0x7C, 0xFC, 0x3C, 0x18

#define LED_MATRIX_CHAR_BLANK    0x00

#define LED_MATRIX_CHAR_A        0x7C, 0x12, 0x12, 0x7C
#define LED_MATRIX_CHAR_B        0x7E, 0x4A, 0x4E, 0x78
#define LED_MATRIX_CHAR_C        0x3C, 0x42, 0x42, 0x24
#define LED_MATRIX_CHAR_D        0x7E, 0x42, 0x42, 0x3C
#define LED_MATRIX_CHAR_E        0x7E, 0x4A, 0x4A, 0x42
#define LED_MATRIX_CHAR_F        0x7E, 0x0A, 0x0A, 0x0A
#define LED_MATRIX_CHAR_G        0x3C, 0x42, 0x52, 0x34
#define LED_MATRIX_CHAR_H        0x7E, 0x08, 0x08, 0x7E
#define LED_MATRIX_CHAR_I        0x42, 0x7E, 0x42
#define LED_MATRIX_CHAR_J        0x20, 0x40, 0x40, 0x3E
#define LED_MATRIX_CHAR_K        0x7E, 0x08, 0x14, 0x62
#define LED_MATRIX_CHAR_L        0x7E, 0x40, 0x40, 0x40
#define LED_MATRIX_CHAR_M        0x7E, 0x04, 0x08, 0x04, 0x7E
#define LED_MATRIX_CHAR_N        0x7E, 0x04, 0x08, 0x7E
#define LED_MATRIX_CHAR_O        0x3C, 0x42, 0x42, 0x3C
#define LED_MATRIX_CHAR_P        0x7E, 0x12, 0x12, 0x0C
#define LED_MATRIX_CHAR_Q        0x3C, 0x42, 0x62, 0x7C, 0x80
#define LED_MATRIX_CHAR_R        0x7E, 0x1A, 0x2A, 0x44
#define LED_MATRIX_CHAR_S        0x44, 0x4A, 0x4A, 0x32
#define LED_MATRIX_CHAR_T        0x02, 0x02, 0x7E, 0x02, 0x02
#define LED_MATRIX_CHAR_U        0x3E, 0x40, 0x40, 0x3E
#define LED_MATRIX_CHAR_V        0x1E, 0x20, 0x40, 0x20, 0x1E
#define LED_MATRIX_CHAR_W        0x3E, 0x40, 0x38, 0x40, 0x3E
#define LED_MATRIX_CHAR_X        0x42, 0x24, 0x18, 0x24, 0x42
#define LED_MATRIX_CHAR_Y        0x02, 0x04, 0x78, 0x04, 0x02
#define LED_MATRIX_CHAR_Z        0x62, 0x52, 0x4A, 0x46

#define LED_MATRIX_CHAR_0        0x3C, 0x42, 0x42, 0x3C
#define LED_MATRIX_CHAR_1        0x02, 0x7E
#define LED_MATRIX_CHAR_2        0x64, 0x52, 0x4A, 0x44
#define LED_MATRIX_CHAR_3        0x42, 0x4A, 0x4A, 0x34
#define LED_MATRIX_CHAR_4        0x0E, 0x08, 0x08, 0x7E
#define LED_MATRIX_CHAR_5        0x4E, 0x4A, 0x4A, 0x32
#define LED_MATRIX_CHAR_6        0x3C, 0x52, 0x52, 0x34
#define LED_MATRIX_CHAR_7        0x02, 0x72, 0x0A, 0x06
#define LED_MATRIX_CHAR_8        0x34, 0x4A, 0x4A, 0x34
#define LED_MATRIX_CHAR_9        0x24, 0x4A, 0x4A, 0x3C

//*****************************************************************************
// External function declarations
//*****************************************************************************

/**************************************************************************//**
*
* led_matrix__init
*
* @brief      initialize LED matrix driver module
*
* @param      -
*
* @return     -
*
******************************************************************************/
void led_matrix_init(void);

/**************************************************************************//**
*
* led_matrix_send_row
*
* @brief      send data to a LED matrix row
*
* @param      row     row number (0-7)
* @param      data    8 bit LED matrix row data
*
* @return     -
*
******************************************************************************/
void led_matrix_send_row(uint8_t row, uint8_t data);

#endif /* _LED_MATRIX_H_*/
