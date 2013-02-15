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
* @file     led_matrix.c
*
* @brief    MSP430 LED Matrix Boosterpack LED Matrix driver source file
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

#include "mss.h"
#include <string.h>
#include "led_matrix.h"

//*****************************************************************************
// Global variables
//*****************************************************************************


//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

#define DATA_LATCH_PIN		BIT4  // P1.4
#define SPI_CLK_OUT_PIN		BIT5  // P1.5
#define SPI_DATA_OUT_PIN	BIT6  // P1.6

#if defined (__MSP430G2452__)
  #define LED_MATRIX_INT_USI_SPI
#elif defined (__MSP430G2553__)
  #define LED_MATRIX_INT_GPIO
  #define SPI_BIT_BANGING_DELAY()         __delay_cycles(5)
#else
  #error This demo only supports either MSP430G2452 or MSP430G2553 as target device
#endif

//*****************************************************************************
// Internal function declarations
//*****************************************************************************

#ifdef LED_MATRIX_INT_GPIO
void spi_send_bit_bang(uint8_t byte);
#endif

//*****************************************************************************
// External functions
//*****************************************************************************

/**************************************************************************//**
*
* led_matrix_init
*
* @brief      initialize LED matrix driver module
*
* @param      -
*
* @return     -
*
******************************************************************************/
void led_matrix_init(void)
{
  // configure SPI pins and latch
  P1DIR |=  DATA_LATCH_PIN | SPI_DATA_OUT_PIN | SPI_CLK_OUT_PIN;

  // set latch pin to inactive
  P1OUT &= ~DATA_LATCH_PIN;

#if defined (LED_MATRIX_INT_USI_SPI)
  // configure SPI
  USICTL0 |= USISWRST;                      // USI in reset
  USICTL0 |= USILSB;                        // Least Significant Bit first
  USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIMST + USIOE; // Port, SPI Master
  USICTL1 |= USICKPH;                       // flag remains set
  //USICKCTL = USISSEL_2 + USIDIV_1;          // SMCLK, inactive low, /2 divider
  USICKCTL = USISSEL_2 + USIDIV_3;          // SMCLK, inactive low, /8 divider
  USICTL0 &= ~USISWRST;                     // USI released for operation
  USICNT |= USI16B + USIIFGCC;              // 16 bit mode; 16 bit to be transmitted/received
#else
  // set both GPIO for SPI communication low
  P1OUT &= ~(SPI_DATA_OUT_PIN | SPI_CLK_OUT_PIN);
#endif
}

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
void led_matrix_send_row(uint8_t row, uint8_t data)
{
  static const uint16_t row_byte[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

#if defined (LED_MATRIX_INT_USI_SPI)
  // put data into the shift register
  USISRH = row_byte[(row&0x07)];
  USISRL = data;

  // set data counter
  USICNT |= 16;

  // wait until data finish
  while(!(USICTL1 & USIIFG));
  USICTL1 &= ~USIIFG;
#else
  // send first byte (data byte)
  spi_send_bit_bang(data);

  // send second byte (row data)
  spi_send_bit_bang(row_byte[(row&0x07)]);
#endif
  
  // output data
  P1OUT |= DATA_LATCH_PIN;
  P1OUT &= ~DATA_LATCH_PIN;
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

#ifdef LED_MATRIX_INT_GPIO
/**************************************************************************//**
*
* spi_send_bit_bang
*
* @brief      send a 8 bit (one byte) SPI data with bit-banging
*
* @param      byte     data to be sent
*
* @return     -
*
******************************************************************************/
void spi_send_bit_bang(uint8_t byte)
{
  uint8_t i;

  for(i=0 ; i<8 ; i++)
  {
	// send LSB
	if(byte & 0x01)
	{
	  P1OUT |= SPI_DATA_OUT_PIN;
	}
	else
	{
	  P1OUT &= ~SPI_DATA_OUT_PIN;
	}

	// delay
	SPI_BIT_BANGING_DELAY();

	// set clock
	P1OUT |= SPI_CLK_OUT_PIN;

	// delay
	SPI_BIT_BANGING_DELAY();

	// reset clock
	P1OUT &= ~SPI_CLK_OUT_PIN;

	// shift right byte
	byte >>= 1;
  }

  // reset SPI data line
  P1OUT &= ~SPI_DATA_OUT_PIN;
}
#endif
