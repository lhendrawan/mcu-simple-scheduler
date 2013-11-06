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
* @file     llist.c
* 
* @brief    single linked list library source file
*
* @version  0.2.1
* 
* @author   Leo Hendrawan
*
* @remark 
* 
******************************************************************************/

//*****************************************************************************
// Include section
//*****************************************************************************

#include "dev_types.h"
#include "llist.h"

#if (MAX_NUM_OF_LLIST > 0)

//*****************************************************************************
// Global variables 
//*****************************************************************************


//*****************************************************************************
// Macros (defines), data types, static variables
//*****************************************************************************

// data structure definition of llist_t
struct llist_tbl_t {
  void *first;  // first object in the linked list
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE)
  void *last;   // last object in the linked list
#endif  
};

// linked list data header
typedef struct {
  void *next;
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE)
  void *prev;  
#endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE) */
} llist_hdr_t;

// table of linked list
static struct llist_tbl_t ll_tbl[MAX_NUM_OF_LLIST];

// number of created single linked list
static uint8_t num_of_ll = 0;

//*****************************************************************************
// Internal function declarations
//*****************************************************************************

/* local llist add function */
static void ll_add(llist_t hdl, void* object, bool first);

//*****************************************************************************
// External functions
//*****************************************************************************

/**************************************************************************//**
*
* llist_create
*
* @brief      create a (single) linked list
*
* @param      -
*
* @return     LLIST_INVALID_HDL - failed to create linked list
*             other - handle of the created single linked list
*
******************************************************************************/
llist_t llist_create(void)
{
  llist_t ret_hdl = LLIST_INVALID_HDL;

  // check number of created single linked list
  if(num_of_ll < MAX_NUM_OF_LLIST)
  {
    // return pointer to the single linked list table
    ret_hdl = &ll_tbl[num_of_ll++];

    // initialize table item
    ret_hdl->first = NULL;
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE)
    ret_hdl->last = NULL;
#endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE) */
  }
  
  return ret_hdl;
}

/**************************************************************************//**
*
* llist_add_first
*
* @brief      add an object into the first position of a linked list
*
* @param[in]  hdl      handle of the linked list
*
* @param[in]  object   pointer object to be added into the linked list
*
* @return     -
*
* @remark     the object parameter shall be pointer to a structure in which
*             the first structure list member is a void pointer type variable
*             which will be used by the llist module to link the objects in
*             the linked list
*
******************************************************************************/
void llist_add_first(llist_t hdl, void* object)
{
  ll_add(hdl, object, true);
}

/**************************************************************************//**
*
* llist_add_last
*
* @brief      add an object into the last position of a linked list
*
* @param[in]  hdl      handle of the linked list
*
* @param[in]  object   pointer object to be added into the linked list
*
* @return     -
*
* @remark     the object parameter shall be pointer to a structure in which
*             the first structure list member is a void pointer type variable
*             which will be used by the llist module to link the objects in
*             the linked list
*
******************************************************************************/
void llist_add_last(llist_t hdl, void* object)
{
  ll_add(hdl, object, false);
}

/**************************************************************************//**
*
* llist_touch_first
*
* @brief      get pointer to the first object in the linked list without
*             removing it out of the linked list
*
* @param[in]  hdl      handle of the linked list
*
* @return     pointer to the first object in the linked list, NULL if no
*             object is found in the list
*
******************************************************************************/
void* llist_touch_first(llist_t hdl)
{
  // check parameter
  LLIST_ASSERT(hdl != LLIST_INVALID_HDL);

  return (hdl->first);
}

/**************************************************************************//**
*
* llist_get_first
*
* @brief      remove and return the pointer of the first object of a linked
*             list
*
* @param[in]  hdl      handle of the linked list
*
* @return     pointer to the first object in the linked list, NULL if no
*             object is found in the list
*
******************************************************************************/
void* llist_get_first(llist_t hdl)
{
  void *ret_obj = NULL;

  // check parameters
  LLIST_ASSERT(hdl != LLIST_INVALID_HDL);

  // check whether there is an object in the linked list
  if(hdl->first != NULL)
  {
	  // set return value pointer
	  ret_obj = hdl->first;

  #if (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE)
    if(hdl->last == hdl->first)
    {
      // the only object in list, set pointers as NULL
      hdl->first = NULL;
      hdl->last = NULL;
    }
    else
  #endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST == TRUE) */
    {
      // set new pointer of the first object in linked list
      hdl->first = ((llist_hdr_t*)hdl->first)->next;    
    }
  }

  return ret_obj;
}

/**************************************************************************//**
*
* llist_remove
*
* @brief      remove an object from a linked list
*
* @param[in]  hdl      handle of the linked list
*
* @param[in]  object   pointer of object to be removed from the linked list
*
* @return     -
*
******************************************************************************/
void llist_remove(llist_t hdl, void* object)
{
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
  void* cur_obj, *prev_obj = NULL;
#else
  void* next_obj, *prev_obj = NULL;
#endif

  // check parameters
  LLIST_ASSERT(hdl != LLIST_INVALID_HDL);

  // check whether there is an object in the linked list
  if(hdl->first != NULL)
  {
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
    // point to the first object
    cur_obj = hdl->first;

    while(cur_obj != NULL)
    {
      if(cur_obj == object)
      {
        // object found, move to the next one
        if(prev_obj != NULL)
        {
          ((llist_hdr_t*)prev_obj)->next = ((llist_hdr_t*)cur_obj)->next;
        }
        else
        {
          // this must be the first object in the list
          hdl->first = ((llist_hdr_t*)cur_obj)->next;
        }
        break;
      }

      // move to the next object in linked list
      prev_obj = cur_obj;
      cur_obj = ((llist_hdr_t*)cur_obj)->next;
    }
#else
    next_obj = ((llist_hdr_t*)object)->next;
    prev_obj = ((llist_hdr_t*)object)->prev;
    // check next object
    if(next_obj != NULL)
    {
      ((llist_hdr_t*)next_obj)->prev = prev_obj;
    }
    else
    {
      // this must be the last object
      LLIST_ASSERT(next_obj == hdl->last);
      hdl->last = prev_obj;
    }

    // check prev object
    if(prev_obj != NULL)
    {
      ((llist_hdr_t*)prev_obj)->next = next_obj;
    }
    else
    {
      // this must be the first object
      LLIST_ASSERT(prev_obj == hdl->first);
      hdl->first = next_obj;
    }    
#endif    
  }
}

/**************************************************************************//**
*
* llist_sort
*
* @brief      sort the objects in the linked list by the help of a compare
*             callback function
*
* @param[in]  hdl        handle of the linked list
*
* @param[in]  comp_func  pointer to callback function for comparing two objects
*                        in the linked list. the return value of the callback
*                        function determines whether the first object given is
*                        less (minus return value), equal(zero return value),
*                        or greater (plus return value) than the second object
*
* @return     -
*
******************************************************************************/
void llist_sort(llist_t hdl, int8_t (*comp_func)(void*, void*))
{
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
  void *last_obj1;
#endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE) */  
  void  *obj1, *obj2, *next_obj1, *next_obj2, *temp;
  bool swapped;

  // check parameters
  LLIST_ASSERT((hdl != LLIST_INVALID_HDL) && (comp_func != NULL));

  do
  {
    // reset flag
    swapped = false;

#if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
    for(last_obj1 = NULL, obj1 = hdl->first,
        obj2 = ((obj1 == NULL) ? NULL : ((llist_hdr_t*)obj1)->next);
        obj2 != NULL ;
        obj1 = next_obj1, obj2 = next_obj2)
#else        
    for(obj1 = hdl->first,
        obj2 = ((obj1 == NULL) ? NULL : ((llist_hdr_t*)obj1)->next);
        obj2 != NULL ;
        obj1 = next_obj1, obj2 = next_obj2)
#endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE) */
    {
      if(comp_func(obj1, obj2) > 0)
      {
        // swap the objects
        if(obj1 == hdl->first)
        {
          hdl->first = obj2;
        }

        // update the next pointers
        temp = ((llist_hdr_t*)obj2)->next;
        ((llist_hdr_t*)obj2)->next = obj1;
        ((llist_hdr_t*)obj1)->next = temp;

      #if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
        if(last_obj1 != NULL)
        {
          ((llist_hdr_t*)last_obj1)->next = obj2;
        }

        // set pointers for next iterations
        last_obj1 = obj2;
        next_obj1 = obj1;
        next_obj2 = ((llist_hdr_t*)obj1)->next;
      #else
        // update the prev pointers
        temp = ((llist_hdr_t*)obj1)->prev;
        ((llist_hdr_t*)obj2)->prev = temp;
        ((llist_hdr_t*)obj1)->prev = obj2;
      
        // set pointers for next iterations
        next_obj1 = obj1;
        next_obj2 = ((llist_hdr_t*)obj1)->next;
      #endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE) */

        // set flag
        swapped = true;
      }
      else
      {
        // set pointers for next iterations
      #if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
      	last_obj1 = obj1;
      #endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE) */
        next_obj1 = obj2;
        next_obj2 = ((llist_hdr_t*)obj2)->next;
      }
    }
  }while(swapped == true);
}

#if (LLIST_DEBUG_MODE == TRUE)
/**************************************************************************//**
*
* llist_check
*
* @brief      check the linked list by going through all its objects
*
* @param[in]  hdl        handle of the linked list
* @param[in]  callback   pointer to callback function to check the linked list
*                        objects. if it returns false, the function will abort
*                        and return immediately
*
* @return     -
*
******************************************************************************/
void llist_check(llist_t hdl, bool (*callback)(void*))
{
  void *obj = hdl->first;

  // check parameters
  LLIST_ASSERT((hdl != LLIST_INVALID_HDL) && (callback != NULL));

  while(obj != NULL)
  {
    // pass the object pointer to the callback function
    if(callback(obj) == false)
    {
      obj = NULL;
    }
    else
    {
      // go to next object
      obj = ((llist_hdr_t*)obj)->next;
    }
  }
}
#endif /* (LLIST_DEBUG_MODE == TRUE) */


//*****************************************************************************
// Internal functions
//*****************************************************************************

/**************************************************************************//**
*
* ll_add
*
* @brief      add an object into the first/last position of a linked list
*
* @param[in]  hdl      handle of the linked list
*
* @param[in]  object   object to be added into the linked list (note: the
*                      object data shall be preceded by array of uint8_t with
*                      the size of LLIST_HDR_LEN)
*
* @param[in]  first    if true object will be added at the first position of
*                      linked list, else at the end
*
* @return     -
*
******************************************************************************/
static void ll_add(llist_t hdl, void* object, bool first)
{
#if (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE)
  void* cur_obj;

  // check parameters
  LLIST_ASSERT((hdl != LLIST_INVALID_HDL) && (object != NULL));

  if((first) || (hdl->first == NULL))
  {
    // set the next pointer object as the previous first object
    ((llist_hdr_t*)object)->next = hdl->first;

    // set as the first object in the list
    hdl->first = object;
  }
  else
  {
    // point to the beginning of the list
    cur_obj = hdl->first;

    // search for the last object in list
    while(((llist_hdr_t*)cur_obj)->next != NULL)
    {
      cur_obj = ((llist_hdr_t*)cur_obj)->next;
    }

    // put the object in the end of the list
    ((llist_hdr_t*)cur_obj)->next = object;

    // mark the object as the end of the list
    ((llist_hdr_t*)object)->next = NULL;
  }
#else
  // check parameters
  LLIST_ASSERT((hdl != LLIST_INVALID_HDL) && (object != NULL));

  if(hdl->first == NULL)
  {
    // must be an empty list
    LLIST_ASSERT(hdl->last == NULL);
    
    // put object as the only object in the list
    hdl->first = object;
    hdl->last = object;
    
    // set pointers of the object as NULL since it is the only object in list
    ((llist_hdr_t*)object)->prev = NULL;
    ((llist_hdr_t*)object)->next = NULL;
  }
  else if(first)
  {
    // must not be an empty list
    LLIST_ASSERT((hdl->first != NULL) && (hdl->last != NULL));
    
    // re-arrange prev pointer of the current first object in the list
    ((llist_hdr_t*)hdl->first)->prev = object;
    
    // put object as first object in the list
    ((llist_hdr_t*)object)->next = hdl->first;
    hdl->first = object;
    ((llist_hdr_t*)object)->prev = NULL;
  }
  else
  {
    // must not be an empty list
    LLIST_ASSERT((hdl->first != NULL) && (hdl->last != NULL));
    
    // re-arrange next pointer of the current last object in the list
    ((llist_hdr_t*)hdl->last)->next = object;
    
    // put object as last object in the list
    ((llist_hdr_t*)object)->prev = hdl->last;
    hdl->last = object;
    ((llist_hdr_t*)object)->next = NULL;
  }
#endif /* (LLIST_ENABLE_DOUBLE_LINKED_LIST != TRUE) */
}

#endif /* (MAX_NUM_OF_LLIST > 0) */

