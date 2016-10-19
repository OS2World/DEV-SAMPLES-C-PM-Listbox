/*******************************************************************************
* FILE NAME: xlistevt.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the implementation of classes/functions declared        *
*   in xlistevt.hpp.                                                           *
*                                                                              *
*******************************************************************************/
extern "C"
{
  #define INCL_WINWINDOWMGR
  #include <os2.h>
  #include "listbox.h"
}

#ifndef _XLISTEVT_
  #include "xlistevt.hpp"
#endif


/*------------------------------------------------------------------------------
| ListBox32Event::ListBox32Event                                               |
|                                                                              |
| Construct from an instance of the IEvent class.                              |
------------------------------------------------------------------------------*/
ListBox32Event::ListBox32Event( IEvent &evt ) :
                ListBox32Event::Inherited(evt)
{
}

