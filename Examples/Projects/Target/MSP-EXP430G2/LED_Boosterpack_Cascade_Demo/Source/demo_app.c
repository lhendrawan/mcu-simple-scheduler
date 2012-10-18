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
* @file     demo_app.c
* 
* @brief    MSP430 Launchpad LED Boosterpack Cascade MSS demo source file
*
* @version  0.2.1
* 
* @author   Leo Hendrawan
*
* @remark   This is a demo of MSS running on MSP430G2452 target device on the
*           MSP-EXP430G2 Launchpad with MSP-LED8x8-BOOSTERPACK
*           (https://www.olimex.com/dev/msp-led8x8.html) and MOD-LED8x8
*           (https://www.olimex.com/dev/index.html) from Olimex.
*           To play with the demo, press S2 button to switch on/off the
*           buzzer playing a song, , and give input at the microphone to
*           accelerate the running text
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"
#include "buzzer.h"
#include "led_matrix.h"
#include "demo_app.h"
#include "demo_cfg.h"

//*****************************************************************************
// Global variables 
//*****************************************************************************


//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

// led matrix scan period in ms
#define LED_MATRIX_SCAN_PERIOD_MS       (2)

#define MIC_SAMPLING_TIMER_PERIOD_MS    (1000)

// period of running text data shift
static mss_timer_tick_t running_text_period = RUNNING_TEXT_MOV_PERIOD_MAX_MS;

// event for push button task
#define LED_PB_TSK_PUSH_BUTTON_EVENT     (0x0001)

// task ID - see MSS_TASK_LIST
#define BUZZER_TASK_ID                (0)
#define RUNNING_TEXT_TASK_ID          (1)

#define APP_ASSERT(x)                 if(!(x)) do{__disable_interrupt(); \
	                                              while(1);}while(0)

// timers
static mss_timer_t led_matrix_scan_tmr;
static mss_timer_t running_text_disp_tmr;
static mss_timer_t mic_sampling_tmr;
static mss_timer_t debouncing_tmr;
static mss_timer_t buzzer_tmr;

// running text display data
static const uint8_t running_text_data[] = RUNNING_TEXT_DATA;

// buzzer tone data
static const buzzer_tone_data_t buzzer_tone_data[] = BUZZER_TONE_DATA;

// average value of ADC mic input
static uint16_t adc_avg;
static uint16_t adc_counter = 0;

// number of ADC sample counter - for debugging
uint16_t sample_cnt = 0;

//*****************************************************************************
// Internal function declarations
//*****************************************************************************

static void init_demo(void);
static void measure_adc_mic_avg(void);

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
  init_demo();

  // run mss - shall never return
  mss_run();
}

/**************************************************************************//**
*
* running_text_task
*
* @brief      task handling LED Matrix running text display
*
* @param[in]  param     task parameter input (unused)
*
* @return     -
*
******************************************************************************/
void running_text_task(void *param)
{
  static mss_task_ctx_t running_text_task_ctx = MSS_TASK_CTX_STATE_INIT_VAL;
  static uint16_t first_idx = 0;
  static uint8_t row = 0;
  uint16_t i, j;

  MSS_BEGIN(running_text_task_ctx);

  // trigger timers
  APP_ASSERT(mss_timer_periodic_start(led_matrix_scan_tmr,
		     MSS_TIMER_MS_TO_TICKS(LED_MATRIX_SCAN_PERIOD_MS),
		     MSS_TIMER_MS_TO_TICKS(LED_MATRIX_SCAN_PERIOD_MS)) == true);
  APP_ASSERT(mss_timer_start(running_text_disp_tmr,
		     MSS_TIMER_MS_TO_TICKS(running_text_period)) == true);
  APP_ASSERT(mss_timer_periodic_start(mic_sampling_tmr,
		     MSS_TIMER_MS_TO_TICKS(MIC_SAMPLING_TIMER_PERIOD_MS),
		     MSS_TIMER_MS_TO_TICKS(MIC_SAMPLING_TIMER_PERIOD_MS)) == true);

  // start continuous conversion
  ADC10CTL0 = REFON + MSC + SREF_1 + ADC10SHT_2 + ADC10ON + ADC10IE;
  ADC10CTL1 = INCH_0 + CONSEQ_2 + ADC10DIV_7 + ADC10SSEL_3;
  ADC10AE0 |= BIT0;  // P1.0 as mic input

  // start continuous conversions
  ADC10CTL0 |= ENC + ADC10SC;

  while(1)
  {
    if(mss_timer_check_expired(led_matrix_scan_tmr) == true)
    {
      j = first_idx + row;
      for(i=0 ; i<NUM_OF_LED_MATRIXES ; i++)
      {
      	if(j >= sizeof(running_text_data))
      	{
      	  j = j - sizeof(running_text_data);
      	}

    	// send data
        led_matrix_send_row(row, running_text_data[j]);

    	// go to next led matrix data
    	j += 8;
      }

      // set output latch
      led_matrix_output_latch();

      // increment row
      row++;
      if(row >= 8) row = 0;
    }

    if((mss_timer_check_expired(running_text_disp_tmr) == true))
    {
      // increment starting index
      first_idx++;
      if(first_idx >= sizeof(running_text_data))
      {
        first_idx = 0;
      }

      // re-trigger the timer
      APP_ASSERT(mss_timer_start(running_text_disp_tmr,
             MSS_TIMER_MS_TO_TICKS(running_text_period)) == true);
    }

#define ADC_COUNTER_THRESHOLD   (30)

    if(mss_timer_check_expired(mic_sampling_tmr) == true)
    {
      if(adc_counter >= ADC_COUNTER_THRESHOLD)
      {
    	  // accelerate running text if minimum period hasn't been reached
    	  if((running_text_period > RUNNING_TEXT_MOV_PERIOD_STEP_MS) &&
    	     ((running_text_period-RUNNING_TEXT_MOV_PERIOD_STEP_MS) >=
    	       RUNNING_TEXT_MOV_PERIOD_MIN_MS))
    	  {
            running_text_period -= RUNNING_TEXT_MOV_PERIOD_STEP_MS;
    	  }
    	  else
    	  {
        	running_text_period = RUNNING_TEXT_MOV_PERIOD_MIN_MS;
    	  }
      }
      else
      {
      	// decelerate running text uf maximum limit hasn't been reached
      	if((running_text_period + RUNNING_TEXT_MOV_PERIOD_STEP_MS) <=
      	    RUNNING_TEXT_MOV_PERIOD_MAX_MS)
      	{
          running_text_period += RUNNING_TEXT_MOV_PERIOD_STEP_MS;
      	}
  	    else
  	    {
      	  running_text_period = RUNNING_TEXT_MOV_PERIOD_MAX_MS;
  	    }
      }
      // reset counter
      adc_counter = 0;
      sample_cnt = 0;
    }

    MSS_RETURN(running_text_task_ctx);
  }

  MSS_FINISH();
}

/**************************************************************************//**
*
* buzzer_task
*
* @brief      handling buzzer on LED Matrix boosterpack
*
* @param[in]  param     task parameter input (unused)
*
* @return     -
*
******************************************************************************/
void buzzer_task(void *param)
{
  static mss_task_ctx_t buzzer_task_ctx = MSS_TASK_CTX_STATE_INIT_VAL;
  static bool buzzer_on = false;
  static unsigned int last_tone_idx = 0;

  MSS_BEGIN(buzzer_task_ctx);

  while(1)
  {
    // check deboucing timer which is activeted by GPIO push button interrupt
    if(mss_timer_check_expired(debouncing_tmr) == true)
    {
      if(!(P1IN & BIT3))
      {
        // button is really pushed, toggle buzzer on flag
    	  if(buzzer_on == false)
    	  {
          // start playing buzzer tone from the beginning
    	    buzzer_set_freq(buzzer_tone_data[0].buzzer_freq_cnt);
          APP_ASSERT(mss_timer_start(buzzer_tmr, 
                     buzzer_tone_data[0].delay) == true);
    	    last_tone_idx = 1;

    	    // set flag to play buzzer
    	    buzzer_on = true;
    	  }
    	  else
    	  {
    	    // stop buzzer
          buzzer_set_freq(PAUSE);

          // stop timer buzzer
          mss_timer_stop(buzzer_tmr);

          // set flag to stop playing buzzer
          buzzer_on = false;
    	  }
      }

      // re-set P1.3 to generate interrupt on high-low transition
      P1IES |= BIT3;
      P1IE |= BIT3;
    }

#define BUZZER_DATA_MAX_SIZE     (sizeof(buzzer_tone_data)/sizeof(buzzer_tone_data_t))

    if(buzzer_on == true)
    {
      if(mss_timer_check_expired(buzzer_tmr) == true)
      {
        // play next tone
    	  buzzer_set_freq(buzzer_tone_data[last_tone_idx].buzzer_freq_cnt);
        APP_ASSERT(mss_timer_start(buzzer_tmr, 
                   buzzer_tone_data[last_tone_idx].delay) == true);

        // adjust index
        if(++last_tone_idx >= BUZZER_DATA_MAX_SIZE)
        {
          last_tone_idx = 0;
        }
      }
    }

    MSS_RETURN(buzzer_task_ctx);
  }

  MSS_FINISH();
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

/**************************************************************************//**
*
* init_demo
*
* @brief      initialize demo tasks
*
* @param      -
*
* @return     -
*
******************************************************************************/
static void init_demo(void)
{
  // initialize Launchpad push button and LEDs
  P1DIR |= (BIT0 + BIT6);
  P1OUT &= ~(BIT0 + BIT6);

  // set P1.3 to generate interrupt on high-low transition
  P1IES |= BIT3;
  P1IE |= BIT3;

  // init buzzer driver
  buzzer_init();

  // initialize led matrix driver
  led_matrix_init();

  // create timers
  debouncing_tmr = mss_timer_create(BUZZER_TASK_ID);
  APP_ASSERT(debouncing_tmr != MSS_TIMER_INVALID_HDL);
  buzzer_tmr = mss_timer_create(BUZZER_TASK_ID);
  APP_ASSERT(buzzer_tmr != MSS_TIMER_INVALID_HDL);

  led_matrix_scan_tmr = mss_timer_create(RUNNING_TEXT_TASK_ID);
  APP_ASSERT(led_matrix_scan_tmr != MSS_TIMER_INVALID_HDL);
  running_text_disp_tmr = mss_timer_create(RUNNING_TEXT_TASK_ID);
  APP_ASSERT(running_text_disp_tmr != MSS_TIMER_INVALID_HDL);
  mic_sampling_tmr = mss_timer_create(RUNNING_TEXT_TASK_ID);
  APP_ASSERT(mic_sampling_tmr != MSS_TIMER_INVALID_HDL);

  // measure mic input average value
  measure_adc_mic_avg();
}

/**************************************************************************//**
*
* Port1_Isr
*
* @brief      PORT 1 ISR handle function
*
* @param      -
*
* @return     -
*
******************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Port1_Isr(void)
{
  if(P1IFG & BIT3)
  {
	  // disable interrupt and clear flag
  	P1IE &= ~BIT3;
    P1IFG &= ~BIT3;

    // set timer to PB task
    mss_timer_start(debouncing_tmr, MSS_TIMER_MS_TO_TICKS(20));
  }
}

/**************************************************************************//**
*
* measure_adc_mic_avg
*
* @brief      measure ADC Mic input average
*
* @param      -
*
* @return     -
*
******************************************************************************/
static void measure_adc_mic_avg(void)
{
  uint16_t i;

#define NUM_OF_AVG_SAMPLES          (64)

  // configure ADC
  ADC10CTL0 = REFON + MSC + SREF_1 + ADC10SHT_3 + ADC10ON;
  ADC10CTL1 = INCH_0 + CONSEQ_0 + ADC10DIV_7 + ADC10SSEL_3;
  ADC10AE0 |= BIT0;  // P1.0 as mic input

  // star sampling for getting average value
  adc_avg = 0;
  for(i=0 ; i<NUM_OF_AVG_SAMPLES ; i++)
  {
    // start single conversion
    ADC10CTL0 |= ENC + ADC10SC;

    // wait until conversion finished
    while(!(ADC10CTL0 & ADC10IFG));
    ADC10CTL0 &= ~ADC10IFG;

    // calculate average value
    adc_avg += ADC10MEM/NUM_OF_AVG_SAMPLES;
  }

  // turn off ADC
  ADC10CTL0 = 0;
}

/**************************************************************************//**
*
* ADC10_Isr
*
* @brief      ADC10 ISR handle function
*
* @param      -
*
* @return     -
*
******************************************************************************/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_Isr(void)
{
#define ADC_THRESHOLD          (50)

  // clear interrupt
  ADC10CTL0 &= ~ADC10IFG;

  // check if conversion exceeds threshold value
  if(ADC10MEM > (adc_avg + ADC_THRESHOLD))
  {
    adc_counter++;
  }
  
  sample_cnt++;
}



/**************************************************************************//**
*
* Trap_Isr
*
* @brief      Trap ISR handle function
*
* @param      -
*
* @return     -
*
******************************************************************************/
#pragma vector=PORT2_VECTOR, USI_VECTOR, TIMER0_A1_VECTOR, TIMER0_A0_VECTOR, \
               NMI_VECTOR
__interrupt void Trap_Isr(void)
{
  // lock down the system
  APP_ASSERT(0);
}
