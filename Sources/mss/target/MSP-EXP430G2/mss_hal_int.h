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
* @file     mss_hal_int.h
* 
* @brief    MSS device specific internal module header file
* 
* @version  0.2.0
*
* @author   Leo Hendrawan
* 
* @remark   target device: MSP430G2452 on MSP-EXP430G2 Launchpad
* 
******************************************************************************/

#ifndef _MSS_HAL_INT_H_
#define _MSS_HAL_INT_H_

//*****************************************************************************
// Include section
//*****************************************************************************

//*****************************************************************************
// Global variable declarations 
//*****************************************************************************


//*****************************************************************************
// Macros (defines) and data types 
//*****************************************************************************

/** MSS_ENABLE_GLOBAL_INTERRUPT
 *  enable global interrupt of the target device. This function is only called
 *  once in @ref mss_run() function.
 */
#define MSS_ENABLE_GLOBAL_INTERRUPT()       __enable_interrupt()

/** mss_task_bits_t
 *  task bits data type - this data type is mainly used to represent a task
 *  (state), and therefore the @ref MSS_NUM_OF_TASKS can not exceed the number
 *  of bits in this data type
 */
typedef uint16_t mss_task_bits_t;

/** MSS_TASK_BIT_POS
 *  array of constant containing task bit position values - used a lot for
 *  setting or resetting a bit in the @ref mss_task_bits_t data type
 */
#define MSS_TASK_BIT_POS                    \
{                                           \
  0x0001, 0x0002, 0x0004, 0x0008,           \
  0x0010, 0x0020, 0x0040, 0x0080,           \
  0x0100, 0x0200, 0x0400, 0x0800,           \
  0x1000, 0x2000, 0x4000, 0x8000            \
}

/*----------------------------------------------------------------------------
   example if mss_task_bits_t is implemented as uint8_t

typedef uint8_t mss_task_bits_t

#define MSS_TASK_BIT_POS                          \
{                                                 \
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80  \
}

----------------------------------------------------------------------------*/


//*****************************************************************************
// External function declarations
//*****************************************************************************

#endif /* _MSS_HAL_INT_H_*/
