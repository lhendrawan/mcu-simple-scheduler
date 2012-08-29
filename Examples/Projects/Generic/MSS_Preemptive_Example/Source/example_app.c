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
* @file     example_app.c
* 
* @brief    mss preemptive application example source file
*
* @version  0.2.0
* 
* @author   Leo Hendrawan
*
* @remark   This is a basic application showing MSS preemptive scheduling
*           capability.
*           There are basically three tasks in the application:
*           int_task, higher_prio_task, and lower_prio_task. int_task has
*           the highest priority (index 0) while lower_prio_task has the
*           lowest priority (index 2). At the beginning, only
*           lower_prio_task is activated (see MSS_READY_TASK_BITS_INIT).
*           When lower_prio_task runs, it will periodically sends an event
*           to activate  higher_prio_task, but it will never release
*           intentionally the scheduler by calling MSS_RETURN() or any other
*           macro functions which encapsulates the MSS_RETURN().
*           However since the scheduler is working preemptively, it will
*           allow the higher_prio_task to run directly after the event has
*           been sent and it will preempt the lower_prio_task. What the
*           higher_prio_task does is basically toggling LED2 with a delay
*           loop without releasing the scheduler.
*           The int_task will be activated periodically from a hardware
*           timer interrupt. The task will also preempt either
*           lower_prio_task or higher_prio_task and do toggling of LED1.
*           If the demo runs correctly, the LED2 will be toggled
*           periodically by higher_prio_task indicating higher_prio_task
*           preempting the lower_prio_task, while sometime the LED1
*           toggled by int_task might also blink indicating that int_task
*           preempting either the higher_prio_task if LED2 is turned on
*           or the lower_prio_task if LED2 is turned off.
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "hal.h"
#include "example_app.h"

//*****************************************************************************
// Global variables 
//*****************************************************************************

//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

#define INT_TASK_ID            (0)
#define HIGHER_PRIO_TASK_ID    (1)
#define LOWER_PRIO_TASK_ID     (2)

#define APP_ASSERT(cond)       HAL_ASSERT(cond)

static mss_timer_t tmr_hdl;

//*****************************************************************************
// Internal function declarations
//*****************************************************************************

static void init_task_app(void);
static void timer_callback_app(void);

//*****************************************************************************
// External functions
//*****************************************************************************

/**************************************************************************//**
*
* main
*
* @brief      main function
*
* @param      -
*
* @return     -
*
******************************************************************************/
void main(void)
{
  // initialize mss
  mss_init();

  // initialize demo application tasks
  init_task_app();

  // run mss - shall never return
  mss_run();
}

/**************************************************************************//**
* 
* int_task
* 
* @brief      task which is called from ISR - highest priority
*
* @param[in]  param     task parameter input (unused)
* 
* @return     -
* 
******************************************************************************/
void int_task(void *param)
{
  static mss_task_ctx_t int_task_ctx = MSS_TASK_CTX_STATE_INIT_VAL;

  MSS_BEGIN(int_task_ctx);

  while(1)
  {
    // toggle LED once
    HAL_LED1_ON();
    MSS_TIMER_DELAY_MS(tmr_hdl, 500, int_task_ctx);
    HAL_LED1_OFF();

    // give CPU
    MSS_RETURN(int_task_ctx);
  }
  
  MSS_FINISH();
}

/**************************************************************************//**
*
* higher_prio_task
*
* @brief      task which is has higher priorty
*
* @param[in]  param     task parameter input (unused)
*
* @return     -
*
******************************************************************************/
void higher_prio_task(void *param)
{
  static mss_task_ctx_t higher_prio_task_ctx = MSS_TASK_CTX_STATE_INIT_VAL;
  mss_event_t my_event;

  MSS_BEGIN(higher_prio_task_ctx);

  // setup Timer_A to setup interrupt
  hal_setup_timer_int(1000, timer_callback_app);

  while(1)
  {
    // wait until it is activated by the lower prio task
	MSS_EVENT_WAIT(my_event, higher_prio_task_ctx);

	if(my_event)
	{
      // toggle LED once
	  HAL_LED2_ON();
	  HAL_DELAY_LOOP_1S();
	  HAL_DELAY_LOOP_1S();
	  HAL_DELAY_LOOP_1S();
	  HAL_LED2_OFF();
	}
  }

  MSS_FINISH();
}

/**************************************************************************//**
*
* lower_prio_task
*
* @brief      task which is has lower priorty
*
* @param[in]  param     task parameter input (unused)
*
* @return     -
*
******************************************************************************/
void lower_prio_task(void *param)
{
  static mss_task_ctx_t lower_prio_task_ctx = MSS_TASK_CTX_STATE_INIT_VAL;

  MSS_BEGIN(lower_prio_task_ctx);

  while(1)
  {
    // set event on the higher priority task
    mss_event_set(HIGHER_PRIO_TASK_ID, 0x01);

	// it never release the CPU except it is preempted by higher prio task
	HAL_DELAY_LOOP_1S();
	HAL_DELAY_LOOP_1S();
	HAL_DELAY_LOOP_1S();
  }

  MSS_FINISH();
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

/**************************************************************************//**
*
* init_task_app
*
* @brief      initialize task application
*
* @param      -
*
* @return     -
*
******************************************************************************/
static void init_task_app(void)
{
  // initialize hal module for MSS demo
  hal_init();

  // create timer
  tmr_hdl = mss_timer_create(INT_TASK_ID);
  APP_ASSERT(tmr_hdl != MSS_TIMER_INVALID_HDL);
}

/**************************************************************************//**
*
* timer_callback_app
*
* @brief      timer callback function for demo application
*
* @param      -
*
* @return     -
*
******************************************************************************/
static void timer_callback_app(void)
{
  // activate int_task
  mss_activate_task(INT_TASK_ID);
}
