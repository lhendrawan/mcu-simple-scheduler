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
* @file     mss_hal.c
* 
* @brief    mcu simple scheduler HAL (hardware abstraction layer) module
*
* @version  0.2.1
*
* @author   Leo Hendrawan
* 
* @remark   target device: 
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "mss_int.h"

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
* mss_hal_init
*
* @brief      initialize mss HAL unit, shall do the following tasks:
*             - setup CPU frequency (if necessary)
*             - if @ref MSS_TASK_USE_TIMER set to TRUE, this function shall
*               setup timer interrupt which shall increment the timer counter
*               mss_timer_tick_cnt and call @ref mss_timer_tick() function 
*               periodically
*             - if @ref MSS_PREEMPTIVE_SCHEDULING is set to TRUE, setup the
*               software interrupt or hardware interrupt which is used to call
*               mss_scheduler during preemption
*
* @param      -
*
* @return     -
*
* @remark     the global interrupt shall not be enabled here
*
******************************************************************************/
void mss_hal_init(void)
{
  // setup CPU frequency, etc.


#if (MSS_TASK_USE_TIMER == TRUE)
  // setup timer interrupt
  
#endif
  
#if (MSS_PREEMPTIVE_SCHEDULING == TRUE)
  // enable software/hardware interrupt used for preemption
#endif /* (MSS_PREEMPTIVE_SCHEDULING == TRUE) */

  // enable global maskable interrupt

}

/**************************************************************************//**
*
* mss_hal_sleep
*
* @brief      do sleep if no task is active - should return/wake up upon
*             interrupt events
*
* @param[in]  sleep_timeout   sleep timeout in ticks (if MSS_SLEEP_NO_TIMEOUT,
*                             no sleep timeout) - can be used as delay to call
*                             mss_timer_tick until the next timer tick
*                             of the youngest timer when the device is
*                             sleeping
*
* @return     -
*
* @remark     this function shall enable interrupt to wake up the CPU from
*             sleep mode and then disable the interrupt before leaving
*             the function
*
******************************************************************************/
#if (MSS_TASK_USE_TIMER == TRUE)
void mss_hal_sleep(mss_timer_tick_t sleep_timeout)
#else
void mss_hal_sleep(void)
#endif /* (MSS_TASK_USE_TIMER == TRUE) */
{

}

#if (MSS_PREEMPTIVE_SCHEDULING == TRUE)
/**************************************************************************//**
*
* mss_hal_trigger_sw_int
*
* @brief      trigger software interrupt - the triggered software interrupt
*             shall call mss_scheduler to do the preemption
*
* @param      -
*
* @return     -
*
******************************************************************************/
void mss_hal_trigger_sw_int(void)
{

}
#endif /* (MSS_PREEMPTIVE_SCHEDULING == TRUE) */

/**************************************************************************//**
*
* mss_get_highest_prio_task
*
* @brief      get the highest priority task (LSB bit position of the
*             task ready bits)
*
* @param[in]  ready_bits    the task bits input
*
* @return     LSB bit position or MSS_INVALID_TASK_ID if not bit is set
*
* @remark     the reason that this function is placed under the hardware
*             dependent (hal) code is to enable optimization since this
*             function is used quite often and can affect the scheduler
*             performance
*
******************************************************************************/
uint8_t mss_get_highest_prio_task(mss_task_bits_t ready_bits)
{
  // todo

  return MSS_INVALID_TASK_ID;
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

