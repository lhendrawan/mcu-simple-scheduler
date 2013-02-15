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
* @file     mque_app.c
* 
* @brief    mss mque application example source file
*
* @version  0.2.1
*
* @author   Leo Hendrawan
* 
* @remark   This is a simple example application showing basic usage of
*           MSS message queue (mque) module.
*           There are two tasks implemented in this example: task_1 and
*           task_2. The second task task_2 will periodically send
*           ASCII messages to the task_1 via the message queue. The first
*           task task_1 will toggle a LED upon receiving certain message.
*           If the application works correctly, LED2 should toggle every
*           1000ms while LED1 toggling every 500 ms.
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "hal.h"
#include "mque_app.h"

#include <string.h>

//*****************************************************************************
// Global variables 
//*****************************************************************************

//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

mss_task_ctx_t task1_ctx = MSS_TASK_CTX_STATE_INIT_VAL;
mss_task_ctx_t task2_ctx = MSS_TASK_CTX_STATE_INIT_VAL;

#define TASK_1_ID                     (0)
#define TASK_2_ID                     (1)

// memory handle for message queue
static mss_mem_t mem_hdl;

#define MQUE_MEM_NUM_OF_BLKS             (4)
#define MQUE_MEM_BLK_SIZE                (4)

#define APP_ASSERT(cond)                HAL_ASSERT(cond)

// mque handle
static mss_mque_t mque_hdl;

// timer handle
static mss_timer_t timer_hdl;

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
  mss_mque_msg_t* msg;

  MSS_BEGIN(task1_ctx);

  while(1)
  {
    // wait for any message in the mque
    MSS_MQUE_WAIT_MSG(mque_hdl, msg, task1_ctx);

    // evaluate message
    if(!memcmp((const char*)msg->data, "LED", 3))
    {
      if(msg->data[3] == '1')
      {
        HAL_LED1_TOGGLE();
      }
      else if(msg->data[3] == '2')
      {
        HAL_LED2_TOGGLE();
      }
    }

    // return memory
    mss_mem_free(mem_hdl, msg);
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
  static uint8_t counter = 0;
  mss_mque_msg_t* msg;

  MSS_BEGIN(task2_ctx)

  while(1)
  {
    switch(counter)
    {
      case 0:
        // allocate msg
    	msg = (mss_mque_msg_t*) mss_mem_alloc(mem_hdl);
    	APP_ASSERT(msg != NULL);

    	// create message
        memcpy(msg->data, "LED1", 4);

        // send message
        mss_mque_send(mque_hdl, msg);

      case 1:

        // allocate msg
      	msg = (mss_mque_msg_t*) mss_mem_alloc(mem_hdl);
      	APP_ASSERT(msg != NULL);

      	// create message
        memcpy(msg->data, "LED2", 4);

        // send message
        mss_mque_send(mque_hdl, msg);

        break;


    }

    // increment counter
    counter = ++counter & 0x01;

    // delay
    MSS_TIMER_DELAY_MS(timer_hdl, 500, task2_ctx);
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

  // create memory for message queue
  mem_hdl = mss_mem_create(MQUE_MEM_BLK_SIZE + sizeof(void*),
		                   MQUE_MEM_NUM_OF_BLKS);
  APP_ASSERT(mem_hdl != MSS_MEM_INVALID_HDL);

  // activate task 1 for the first time
  mss_activate_task(TASK_1_ID);

  // create message queue
  mque_hdl = mss_mque_create(TASK_1_ID);
  APP_ASSERT(mque_hdl != MSS_MQUE_INVALID_HDL);

  // create timer
  timer_hdl = mss_timer_create(TASK_2_ID);
  APP_ASSERT(timer_hdl != MSS_TIMER_INVALID_HDL);
}

