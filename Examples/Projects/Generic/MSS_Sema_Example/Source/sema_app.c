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
* @file     sema_app.c
* 
* @brief    mss semaphore application example source file
*
* @version  0.2.0
*
* @author   Leo Hendrawan
* 
* @remark   This example shows a basic application example of using MSS
*           Semaphore module.
*           There are two tasks implemented in this module: task_1 and
*           task_2. Each task's job is basically to toggle a LED (task_1
*           toggling LED1, task_2 toggling LED2) with different period.
*           However before a task tries to turn on a LED, it will first try
*           to wait for the created semaphore, and it will block as long as
*           the semaphore is not available (locked by the other task).
*           If the example runs correctly, the LED2 can only blink as long
*           as LED1 is turned off. When LED1 is turned on, the LED2 will
*           stay off indicating task_2 is trying to wait for the semaphore
*           becoming available.
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "hal.h"
#include "sema_app.h"

//*****************************************************************************
// Global variables 
//*****************************************************************************

//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

struct app_task_t {
  mss_task_ctx_t ctx_state;
  mss_timer_t timer_hdl;
};

struct app_task_t task1_ctx = {MSS_TASK_CTX_STATE_INIT_VAL, MSS_TIMER_INVALID_HDL};
struct app_task_t task2_ctx = {MSS_TASK_CTX_STATE_INIT_VAL, MSS_TIMER_INVALID_HDL};

mss_sema_t sema_hdl;

#define TASK_1_ID                     (0)
#define TASK_2_ID                     (1)

#define LED_1_FREQ_MS                 (3000)
#define LED_2_FREQ_MS                 (500)

#define APP_ASSERT(cond)                HAL_ASSERT(cond)

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
void task_1(void *param)
{
  MSS_BEGIN(task1_ctx.ctx_state);

  while(1)
  {
    // lock semaphore
    MSS_SEMA_WAIT(sema_hdl, task1_ctx.ctx_state);

    // turn on LED to indicate locking semaphore
    HAL_LED1_ON();

    // delay
    MSS_TIMER_DELAY_MS(task1_ctx.timer_hdl, LED_1_FREQ_MS, task1_ctx.ctx_state);

    // unlock semaphore
    mss_sema_post(sema_hdl);

    // turn off LED to indicate unlocking semaphore
    HAL_LED1_OFF();

    // delay
    MSS_TIMER_DELAY_MS(task1_ctx.timer_hdl, LED_1_FREQ_MS, task1_ctx.ctx_state);
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
  MSS_BEGIN(task2_ctx.ctx_state);
  
  while(1)
  {
    // lock semaphore
	MSS_SEMA_WAIT(sema_hdl, task2_ctx.ctx_state);

    // turn on LED to indicate locking semaphore
    HAL_LED2_ON();
    
    // delay
    MSS_TIMER_DELAY_MS(task2_ctx.timer_hdl, LED_2_FREQ_MS, task2_ctx.ctx_state);
    
    // unlock semaphore
    mss_sema_post(sema_hdl);

    // turn off LED to indicate unlocking semaphore
    HAL_LED2_OFF();

    // delay
    MSS_TIMER_DELAY_MS(task2_ctx.timer_hdl, LED_2_FREQ_MS, task2_ctx.ctx_state);
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
* @brief      initialize example tasks
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

  // create semaphore
  sema_hdl = mss_sema_create(1);

  // create timer
  task1_ctx.timer_hdl = mss_timer_create(TASK_1_ID);
  APP_ASSERT(task1_ctx.timer_hdl != MSS_TIMER_INVALID_HDL);
  task2_ctx.timer_hdl = mss_timer_create(TASK_2_ID);
  APP_ASSERT(task2_ctx.timer_hdl != MSS_TIMER_INVALID_HDL);

}
