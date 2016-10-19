#ifndef _XLISTEVT_
#define _XLISTEVT_
/*******************************************************************************
* FILE NAME: xlistevt.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Declaration of the class(es):                                              *
*   ListBox32Handler - Control event information class for 32-Bit list box.    *
*                                                                              *
*******************************************************************************/
#ifndef _ICTLEVT_
  #include <ictlevt.hpp>
#endif

//Forward declarations
class ListBox32;


/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

class ListBox32Event : public IControlEvent {
typedef IControlEvent
  Inherited;
/*******************************************************************************
*                                                                              *
*******************************************************************************/
public:
/*------------------------------- Constructor ----------------------------------
| The only way to construct instances of this class is from an instance of     |
| the IEvent class.                                                            |
------------------------------------------------------------------------------*/
  ListBox32Event   ( IEvent &event );


private:
/*--------------------------------- PRIVATE ----------------------------------*/
  ListBox32Event  ( const ListBox32Event & );  //copy ctor
  operator =      ( const ListBox32Event & );  //assignment ctor

};  // class ListBox32Event

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif  //_XLISTEVT_
