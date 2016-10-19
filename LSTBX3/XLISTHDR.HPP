#ifndef _XLISTHDR_
#define _XLISTHDR_
/*******************************************************************************
* FILE NAME: xlisthdr.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Declaration of the class(es):                                              *
*   ListBox32Handler - Handler class for 32-Bit list box control.              *
*                                                                              *
*******************************************************************************/
#ifndef _IHANDLER_
  #include <ihandler.hpp>
#endif

#ifndef _XLISTEVT_
  #include "xlistevt.hpp"
#endif

//Forward declarations
class ListBox32;

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

class ListBox32Handler : public IHandler {
typedef IHandler
  Inherited;
/*******************************************************************************
*                                                                              *
*******************************************************************************/
public:
/*-------------------------- Constructor/Destructor ----------------------------
| You can construct generic objects of this class by providing the following:  |
|    o From a pointer to a ListBox32 object.  This ctor will attach the        |
|      handler to the object if the object is provided.                        |
------------------------------------------------------------------------------*/
  ListBox32Handler   ( ListBox32 *listBox = 0 );

virtual
  ~ListBox32Handler  ( );

/*---------------------------- Window Attachment -------------------------------
| handleEventsFor - Attaches this handler to the ListBox32 object.             |
------------------------------------------------------------------------------*/
virtual ListBox32Handler
 &handleEventsFor  ( ListBox32 *listBox );


protected:
/*---------------------------- Event Dispatching -------------------------------
| This function evaluates the event to determine if it is appropriate for      |
| this handler object to process.  If it is, it calls a virtual function used  |
| to process the event.                                                        |
|   dispatchHandlerEvent - Override to process events destined for our         |
|                          "ListBoxWindow" window class.                       |
------------------------------------------------------------------------------*/
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );

/*------------------------ Event Processing Functions --------------------------
| These functions should be supplied by a derived class in order to provide    |
| processing for a selection, enter, or a focus change event.                  |
|   enter     - Implemented by derived classes to process an enter event.      |
|   selected  - Implemented by derived classes to process a selection event.   |
|   gotFocus  - Implemented by derived classes to process a focus gain event.  |
|   lostFocus - Implemented by derived classes to process a focus loss event.  |
|   scroll    - Implemented by derived classes to process a scroll event.      |
|   checked   - Implemented by derived classes to process a check event.       |
------------------------------------------------------------------------------*/
virtual Boolean
  enter      ( const ListBox32Event &event ),
  selected   ( const ListBox32Event &event ),
  gotFocus   ( const ListBox32Event &event ),
  lostFocus  ( const ListBox32Event &event ),
  scroll     ( const ListBox32Event &event ),
  checked    ( const ListBox32Event &event );


private:
/*--------------------------------- PRIVATE ----------------------------------*/
virtual ListBox32Handler
 &handleEventsFor   ( IWindow * );

  ListBox32Handler  ( const ListBox32Handler & );  //copy ctor
  operator =        ( const ListBox32Handler & );  //assignment ctor

};  // class ListBox32Handler


/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif  //_XLISTHDR_
