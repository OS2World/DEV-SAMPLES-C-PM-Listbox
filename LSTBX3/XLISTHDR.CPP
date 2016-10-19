/*******************************************************************************
* FILE NAME: xlisthdr.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the implementation of classes/functions declared        *
*   in xlisthdr.hpp.                                                           *
*                                                                              *
*******************************************************************************/
extern "C"
{
  #define INCL_WINLISTBOXES
  #define INCL_WINWINDOWMGR
  #include <os2.h>
  #include "listbox.h"
}

#ifndef _IWINDOW_
  #include <iwindow.hpp>
#endif
#ifndef _ISTRING_
  #include <istring.hpp>
#endif
#ifndef _IEXCEPT_
  #include <iexcept.hpp>
#endif

#ifndef _XLISTHDR_
  #include "xlisthdr.hpp"
#endif
#ifndef _XLISTBOX_
  #include "xlistbox.hpp"
#endif


/*------------------------------------------------------------------------------
| ListBox32Handler::ListBox32Handler                                           |
|                                                                              |
| Construct from a pointer to a ListBox32 object.  This ctor will attach the   |
| handler to the object if the object is provided.                             |
------------------------------------------------------------------------------*/
ListBox32Handler::ListBox32Handler( ListBox32 *pLB ) : IHandler( )
{
  if (pLB)
    handleEventsFor( pLB );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::~ListBox32Handler                                          |
|                                                                              |
| Default destructor                                                           |
------------------------------------------------------------------------------*/
ListBox32Handler::~ListBox32Handler()
{
}

/*------------------------------------------------------------------------------
| ListBox32Handler::handleEventsFor                                            |
|                                                                              |
| Attaches this handler to the ListBox32 object.                               |
------------------------------------------------------------------------------*/
ListBox32Handler& ListBox32Handler::handleEventsFor( ListBox32 *pLB )
{
  Inherited::handleEventsFor( pLB );
  return( *this );
};

/*------------------------------------------------------------------------------
| ListBox32Handler::dispatchHandlerEvent                                       |
|                                                                              |
| Process control events destined for our "ListBoxWindow" window class.        |
| True is returned if event was processed.  Otherwise, false is returned       |
| to give the next handler in the chain (if any) an opportunity to process.    |
| If no handlers process the event, then default PM processing will occur.     |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::dispatchHandlerEvent( IEvent &evt )
{
  Boolean bRC = false;

  /***************************************************************/
  /* Only process control events ....                            */
  /***************************************************************/
  if (evt.eventId() == WM_CONTROL)
  {
    IControlEvent ctlevt(evt);
    unsigned long ulMsg = ctlevt.parameter1().number2();
    IWindow* pwndControl = ctlevt.controlWindow();

    /*************************************************************/
    /* This handler is either attached to the control generating */
    /* the WM_CONTROL message or to its owner.  If               */
    /* IControlEvent::controlWindow returns 0, this must mean we */
    /* have a non-wrappered control with a wrappered owner       */
    /* window and that the handler is attached to the owner      */
    /* window.  This case is supported only if the owner of the  */
    /* control is also the control's parent (this is in order    */
    /* for handleWithId to work).                                */
    /*************************************************************/
    IWindowHandle hwndControl;
    if (pwndControl)
    {
       hwndControl = pwndControl->handle();
    }
    else
    {
       hwndControl = IWindow::handleWithId( ctlevt.controlId(),
                                            ctlevt.handle() );
    }

    if (hwndControl)
    {
      IString className = IString( 0, 16 );
      WinQueryClassName( hwndControl, className.length()+1, className );

      /***********************************************************/
      /* ... for the 32-Bit list box.                            */
      /***********************************************************/
      if (className == "ListBoxWindow")
      {
        if (ulMsg == LN_SELECT)
        {
          bRC = selected( ctlevt );
        }
        else if (ulMsg == LN_ENTER)
        {
          bRC = enter( ctlevt );
        }
        else if (ulMsg == LN_SETFOCUS)
        {
          bRC = gotFocus( ctlevt );
        }
        else if (ulMsg == LN_KILLFOCUS)
        {
          bRC = lostFocus( ctlevt );
        }
        else if (ulMsg == LN_SCROLL)
        {
          bRC = scroll( ctlevt );
        }
        else if (ulMsg == LNX_CHECKED)
        {
          bRC = checked( ctlevt );
        }
      }

      /***********************************************************/
      /* Processing complete ... Set result if event was         */
      /* processed.                                              */
      /***********************************************************/
      if (bRC)
         evt.setResult(ctlevt.result());
    }
  } /* endif WM_CONTROL */

  return( bRC );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::enter                                                      |
|                                                                              |
| Dummy virtual handler function.  Derived classes override to process the     |
| enter event.                                                                 |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::enter ( const ListBox32Event &evt )
{
  return( false );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::selected                                                   |
|                                                                              |
| Dummy virtual handler function.  Derived classes override to process the     |
| selection event.                                                             |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::selected ( const ListBox32Event &evt )
{
  return( false );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::gotFocus                                                   |
|                                                                              |
| Dummy virtual handler function.  Derived classes override to process the     |
| focus gain event.                                                            |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::gotFocus ( const ListBox32Event &evt )
{
  return( false );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::lostFocus                                                  |
|                                                                              |
| Dummy virtual handler function.  Derived classes override to process the     |
| focus loss event.                                                            |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::lostFocus ( const ListBox32Event &evt )
{
  return( false );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::scroll                                                     |
|                                                                              |
| Dummy virtual handler function.  Derived classes override to process the     |
| scroll event.                                                               |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::scroll ( const ListBox32Event &evt )
{
  return( false );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::checked                                                    |
|                                                                              |
| Dummy virtual handler function.  Derived classes override to process the     |
| checked event.                                                               |
------------------------------------------------------------------------------*/
Boolean ListBox32Handler::checked ( const ListBox32Event &evt )
{
  return( false );
}

/*------------------------------------------------------------------------------
| ListBox32Handler::handleEventsFor                                (private)   |
|                                                                              |
| Defined to prevent accidental usage.  Function defined to accept ListBox32 * |
| is the handleEventsFor that only should be used.                             |
------------------------------------------------------------------------------*/
ListBox32Handler& ListBox32Handler::handleEventsFor( IWindow * )
{
  return( *this );
};
