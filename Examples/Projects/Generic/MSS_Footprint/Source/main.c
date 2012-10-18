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
* @file     main.c
*
* @brief    mss footprint dummy main file
*
* @version  0.2.1
*
* @author   Leo Hendrawan
*
* @remark   just a dummy main file to enable compilation for measuring the
*           memory footprint of MSS with activated modules in mss_cfg.h
*
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "mss.h"

/**
 * @ingroup   MSS_GENERIC_EXAMPLE
 * @defgroup  MSS_Footprint_Example    MSS Footprint Example
 * @remark    This is a a very simple example to calculate the memory
 *            requirement/footprint of MSS.
 *            Per default all MSS features (timers, semaphores, etc.) are
 *            enabled the configuration files which can be changed if
 *            necessary to calculate the required memory.
 */

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

void main(void)
{
  // initialize mss
  mss_init();

  // run mss - shall never return
  mss_run();
}

//*****************************************************************************
// Internal functions
//*****************************************************************************

