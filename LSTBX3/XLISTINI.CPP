/*******************************************************************************
* FILE NAME: xlistini.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains DLL initialization termination routine.                 *
*                                                                              *
*******************************************************************************/
#include <stdio.h>

// function prototypes
extern "C"
{
  int  _CRT_init      (void );
  void __ctordtorInit (void );
}

unsigned long _System _DLL_InitTerm (unsigned long hmodule,
                                     unsigned long ulFlag )
{
  unsigned long ulRC = 1;         // assume no errors

  if (ulFlag == 0)
  {                               // DLL being loaded
     if (_CRT_init() == -1)
       ulRC = 0;                  // error
     else
       __ctordtorInit();
  }
  else
  {
    if (ulFlag == 1)
    {                             // DLL being freed
      //Since we are only linking dynamically, we do not need to
      //perform termination processing.  If we were linking statically,
      //we would need to call __ctordtorTerm() and _CRT_term() here in
      //that order.
    }
    else
      ulRC = 0;                   // error
  }

  return( ulRC );
}
