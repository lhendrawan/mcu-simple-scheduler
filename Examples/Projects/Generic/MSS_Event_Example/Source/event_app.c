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
* @file     event_app.c
* 
* @brief    mss event application example source file
*
* @version  0.2.1
* 
* @author   Leo Hendrawan
*
* @remark   This is a simple example application showing basic usage of
*           MSS event module.
*           There are two tasks implemented in the application: task_1 and
*           task_2. The first task task_1 will periodically send two types
*           of events to the task_2. The second task task_2 will toggle a
*           LED upon receiving certain event.
*           If the application works correctly, LED1 should toggle every
*           500ms while LED2 toggling every 1000 ms.
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "hal.h"
#include "event_app.h"

//*****************************************************************************
// Global variables 
//*****************************************************************************

//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

// task 1 variable
static mss_task_ctx_t ctx_state_1 = MSS_TASK_CTX_STATE_INIT_VAL;
static mss_timer_t timer_hdl_toggle_led1;
static mss_timer_t timer_hdl_toggle_led2;


// task 2 variable
static mss_task_ctx_t ctx_state_2 = MSS_TASK_CTX_STATE_INIT_VAL;

#define APP_ASSERT(cond)                HAL_ASSERT(cond)

#define TASK_1_ID                       (0)
#define TASK_2_ID                       (1)

#define LED_1_TOGGLE_MS                 (500)
#define LED_2_TOGGLE_MS                 (1000)

#define LED_1_TOGGLE_EVENT              (0x01)
#define LED_2_TOGGLE_EVENT              (0x02)

//*****************************************************************************
// Internal function declarations
//*****************************************************************************

static void init_tasks(void);

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

  // initialize tasks
  init_tasks();

  // run mss - shall never return
  mss_run();
}

/**************************************************************************//**
* 
* task_1
* 
* @brief      task 1 example
*
* @param[in]  param     task parameter input (unused)
* 
* @return     -
* 
******************************************************************************/
void task_1(void* param)
{
  MSS_BEGIN(ctx_state_1);
  
  // set timer
  APP_ASSERT(mss_timer_start(timer_hdl_toggle_led1, LED_1_TOGGLE_MS) == true);
  APP_ASSERT(mss_timer_periodic_start(timer_hdl_toggle_led2, LED_2_TOGGLE_MS,
		                              LED_2_TOGGLE_MS) == true);

  while(1)
  {
    if(mss_timer_check_expired(timer_hdl_toggle_led1) == true)
    {
      // send event to task 2 to toggle LED 1
      mss_event_set(TASK_2_ID, LED_1_TOGGLE_EVENT);

      // set the timer again
      mss_timer_start(timer_hdl_toggle_led1, LED_1_TOGGLE_MS);
    }

    if(mss_timer_check_expired(timer_hdl_toggle_led2) == true)
    {
      // send event to task 2 to toggle LED 2
      mss_event_set(TASK_2_ID, LED_2_TOGGLE_EVENT);
    }

    // suspend task until next timer fires
    MSS_RETURN(ctx_state_1);
  }
  
  MSS_FINISH();
}

/**************************************************************************//**
* 
* task_2
* 
* @brief      task 2 example
*
* @param[in]  param     task parameter input (unused)
* 
* @return     -
* 
******************************************************************************/
void task_2(void *param)
{
  mss_event_t event;

  MSS_BEGIN(ctx_state_2);

  while(1)
  {
	// wait for an event event
	MSS_EVENT_WAIT(event, ctx_state_2);

    if(event & LED_1_TOGGLE_EVENT)
    {
      // toggle LED 1
      HAL_LED1_TOGGLE();
    }

    if(event & LED_2_TOGGLE_EVENT)
    {
      // toggle LED 2
      HAL_LED2_TOGGLE();
    }
  }
  
  MSS_FINISH();
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

/**************************************************************************//**
*
* init_tasks
*
* @brief      initialize tasks
*
* @param      -
*
* @return     -
*
******************************************************************************/
static void init_tasks(void)
{
  // initialize hal module for MSS demo
  hal_init();

  // create timer
  timer_hdl_toggle_led1 = mss_timer_create(TASK_1_ID);
  APP_ASSERT(timer_hdl_toggle_led1 != MSS_TIMER_INVALID_HDL);
  timer_hdl_toggle_led2 = mss_timer_create(TASK_1_ID);
  APP_ASSERT(timer_hdl_toggle_led2 != MSS_TIMER_INVALID_HDL);
}

