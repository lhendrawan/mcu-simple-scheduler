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
* @file     timer_app.c
* 
* @brief    mss timer application example source file
*
* @version  0.2.1
*
* @author   Leo Hendrawan
* 
* @remark   This is a simple example application showing basic usage of
*           MSS timer module. This example also shows how to use one
*           physical task code for several (two) tasks.
*           There are basically two tasks implemented, but both uses the
*           same code task_app. The difference between the task is only
*           the task parameter pointer passed to each task. Each task
*           will toggle a LED with different period.
*           If the application works correctly, LED1 should toggle every
*           500ms while LED2 toggling every 1000 ms.
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "timer_app.h"
#include "hal.h"

//*****************************************************************************
// Global variables 
//*****************************************************************************

//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

struct app_task_t {
  mss_task_ctx_t ctx_state;
  mss_timer_t timer_hdl;
  uint16_t freq;
  uint16_t led_num;
};

struct app_task_t task1_ctx = {MSS_TASK_CTX_STATE_INIT_VAL, MSS_TIMER_INVALID_HDL, 0, 0};
struct app_task_t task2_ctx = {MSS_TASK_CTX_STATE_INIT_VAL, MSS_TIMER_INVALID_HDL, 0, 0};

#define TASK_1_ID                     (0)
#define TASK_2_ID                     (1)

#define LED_1_FREQ_MS                 (500)
#define LED_2_FREQ_MS                 (1000)

#define APP_ASSERT(cond)              HAL_ASSERT(cond)

//*****************************************************************************
// Internal function declarations
//*****************************************************************************

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
  init_task_app();

  // run mss - shall never return
  mss_run();
}

/**************************************************************************//**
* 
* init_task_1
* 
* @brief      initialize task 1 example
*
* @param      -
* 
* @return     -
* 
******************************************************************************/
void init_task_app(void)
{
  // init hal
  hal_init();

  // initialize parameters
  task1_ctx.led_num = 1;
  task1_ctx.freq = LED_1_FREQ_MS;

  task2_ctx.led_num = 2;
  task2_ctx.freq = LED_2_FREQ_MS;

  // create timers
  task1_ctx.timer_hdl = mss_timer_create(TASK_1_ID);
  APP_ASSERT(task1_ctx.timer_hdl != MSS_TIMER_INVALID_HDL);
  task2_ctx.timer_hdl = mss_timer_create(TASK_2_ID);
  APP_ASSERT(task2_ctx.timer_hdl != MSS_TIMER_INVALID_HDL);
}

/**************************************************************************//**
* 
* task_app
* 
* @brief      timer task example
*
* @param[in]  param     task parameter input 
* 
* @return     -
* 
******************************************************************************/
void task_app(void *param)
{
  struct app_task_t	*variables = (struct app_task_t*)param;

  MSS_BEGIN(variables->ctx_state);

  while(1)
  {
     // toggle LED
	hal_toggle_led(variables->led_num);

    // delay
    MSS_TIMER_DELAY_MS(variables->timer_hdl, variables->freq, variables->ctx_state);
  }
  
  MSS_FINISH();
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

