/******************************************************************************
* README.txt 
*
* MSS - MCU Simple Scheduler 
*
* version : 0.2.1
*
******************************************************************************/

MSS (MCU Simple Sceheduler) is a light-weight, preemptable, and portable
scheduler system offering multi-tasking capability for small 8/16 bit
microcontrollers with other basic features such as timers, event flags,
message queues, and semaphores.

/******************************************************************************
* Documentation
******************************************************************************/

Go to <ROOT_DIRECTORY>/Docs/html/index.html for the MSS documentation

/******************************************************************************
* Directory Structures 
******************************************************************************/

<ROOT_DIRECTORY>
  |
  |- Docs : documentation stuffs
  |
  |- Examples : project code and examples
  |   |
  |   |- hal : hardware abstraction layer code for the Generic example codes
  |   |
  |   |- Projects : project codes
  |   |   |
  |   |   |- Generic : generic example codes and projects for all supported
  |   |   |            hardware platforms
  |   |   |
  |   |   |- Target : target specific example codes and projects
  |    
  |- Sources : MSS codes 
      |
      |- llist : linked list (llist) source codes
      |
      |- mss : MSS source codes folders
          |
	  |- common : hardware independent MSS source codes
	  |
	  |- target : hardware dependent MSS source codes
          |
	  |- templates : template folders
	      |
	      |- configuration : templates of llist_cfg.h and mss_cfg.h
	      |
	      |- target : templates for hardware dependent source code
	      
