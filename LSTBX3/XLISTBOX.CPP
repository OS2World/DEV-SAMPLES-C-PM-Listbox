/*******************************************************************************
* FILE NAME: xlistbox.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the implementation of classes/functions declared        *
*   in xlistbox.hpp.                                                           *
*                                                                              *
*******************************************************************************/
extern "C"
{
  #define INCL_WINLISTBOXES      // LIT_
  #define INCL_WINSYS            // System values and Colors
  #define INCL_WINWINDOWMGR      // WinQueryWindowULong
  #define INCL_DOSMODULEMGR      // DosLoadModule
  #include <os2.h>
  #include "listbox.h"
}

#ifndef _ISTRING_
  #include <istring.hpp>
#endif
#ifndef _ITHREAD_
  #include <ithread.hpp>
#endif
#ifndef _IEXCEPT_
  #include <iexcept.hpp>
#endif

#ifndef _XLISTBOX_
  #include "xlistbox.hpp"
#endif

/***************************************************************/
/* Public list box styles.                                     */
/***************************************************************/
const ListBox32::ExtendedStyle
  ListBox32::checkBox                  = LSXS_CHECKBOX,
  ListBox32::classDefaultExtendedStyle = 0;

/***************************************************************/
/* Default style for new objects (initial value)               */
/***************************************************************/
ListBox32::ExtendedStyle ListBox32::currentDefaultExtendedStyle = 0;


/*------------------------------------------------------------------------------
| ListBox32::ListBox32                                                         |
|                                                                              |
| Construct a ListBox32 on an IWindow.                                         |
------------------------------------------------------------------------------*/
ListBox32::ListBox32( unsigned long ulId,
                      IWindow *pParent,
                      IWindow *pOwner,
                      const IRectangle &rectInit,
                      const Style &style,
                      const ExtendedStyle &extendedStyle ) :
           IListBox( createListBox( ulId, pParent, pOwner, rectInit,
                                    style, extendedStyle ) ),
                      ulExtendedStyle( extendedStyle.asUnsignedLong() ),
                      bSoundSupported( 0 )
{
  initialize();
}

/*------------------------------------------------------------------------------
| ListBox32::ListBox32                                                         |
|                                                                              |
| Construct a ListBox32 on a dialog.                                           |
------------------------------------------------------------------------------*/
ListBox32::ListBox32( unsigned long ulId, IWindow* parent ) :
           IListBox( validate( WinWindowFromID(parent->handle(), ulId) ) ),
                      bSoundSupported( 0 )
{
  initialize();
}

/*------------------------------------------------------------------------------
| ListBox32::ListBox32                                                         |
|                                                                              |
| Wrapper an existing ListBox.                                                 |
------------------------------------------------------------------------------*/
ListBox32::ListBox32( const IWindowHandle &handle ) :
           IListBox( validate( handle ) ),
                      bSoundSupported( 0 )
{
  initialize();
}

/*------------------------------------------------------------------------------
| ListBox32::~ListBox32                                                        |
|                                                                              |
| Default destructor                                                           |
------------------------------------------------------------------------------*/
ListBox32::~ListBox32()
{
}

/*------------------------------------------------------------------------------
| ListBox32::createListBox                                                     |
|                                                                              |
| Static function that creates the 32-Bit list box.                            |
------------------------------------------------------------------------------*/
IWindowHandle ListBox32::createListBox(unsigned long       ulId,
                                       IWindow             *pParent,
                                       IWindow             *pOwner,
                                       const IRectangle    &rectInit,
                                       const Style         &style,
                                       const ExtendedStyle &extendedStyle)
{
  /***************************************************************/
  /* Assertions on input parms                                   */
  /***************************************************************/
  IASSERTPARM(pParent!=0);

  /***************************************************************/
  /* Register the 32-Bit list box class                          */
  /***************************************************************/
  if (!fRegisterListBox( IThread::current().anchorBlock() ))
    ITHROWGUIERROR( "fRegisterListBox" );

  /***************************************************************/
  /* Build the control data structure for the 32-Bit list box    */
  /***************************************************************/
  LISTBOXCDATA ctlData;
  memset(&ctlData, 0, sizeof(LISTBOXCDATA));
  ctlData.cb = sizeof(LISTBOXCDATA);
  ctlData.ulVersion = LBV_110;
  ctlData.vdata.lbcd1_1.flExtStyles = extendedStyle.asUnsignedLong();

  /***************************************************************/
  /* Create the 32-Bit list box                                  */
  /***************************************************************/
  IWindowHandle hwndLB = WinCreateWindow( pParent->handle(),
                                          "ListBoxWindow",
                                          0,
                                          style.asUnsignedLong(),
                                          rectInit.left(),
                                          rectInit.bottom(),
                                          rectInit.width(),
                                          rectInit.height(),
                                          (pOwner==0) ? IWindowHandle(0) :
                                                        pOwner->handle(),
                                          HWND_TOP,
                                          ulId,
                                          &ctlData,
                                          0 );
  if (hwndLB == 0)
  {
    ITHROWGUIERROR(IString("WinCreateWindow: Id=") +
                   IString(ulId) +
                   IString(" Class=ListBoxWindow"));
  }

  return( hwndLB );
}

/*------------------------------------------------------------------------------
| ListBox32::validate                                                          |
|                                                                              |
| Static function that validates the window handle.                            |
------------------------------------------------------------------------------*/
IWindowHandle ListBox32::validate( const IWindowHandle &handle )
{
  /***************************************************************/
  /* Verify the window handle                                    */
  /***************************************************************/
  IASSERTPARM( handle.isValid() );

  /***************************************************************/
  /* Verify that the window class is "ListBoxWindow"             */
  /***************************************************************/
  IString className = IString( 0, 16 );
  WinQueryClassName( handle, className.length()+1, className );
  IASSERTSTATE( className == "ListBoxWindow" );

  return( handle );
}

/*------------------------------------------------------------------------------
| ListBox32::initialize                                                        |
|                                                                              |
| Perform initialization tasks that are common across the ctors.               |
------------------------------------------------------------------------------*/
void ListBox32::initialize( )
{
  HMODULE hmod;

  /***************************************************************/
  /* I know, I know, but this is the easiest way to determine    */
  /* if the sound support is available.                          */
  /***************************************************************/
  if (!DosLoadModule(NULL, 0, "LBSnd", &hmod))
    this->bSoundSupported = true;
}

/*------------------------------------------------------------------------------
| ListBox32::check                                                             |
|                                                                              |
| Set an item as checked in the list.                                          |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::check(unsigned long index, Boolean turnOn)
{
  IEventResult evt = handle().sendEvent(LMX_SETCHECK,
                                        IEventParameter1(index),
                                        IEventParameter2(turnOn));
  if (!(evt.asUnsignedLong()))
     ITHROWGUIERROR("LMX_SETCHECK");

  return( *this );
};

/*------------------------------------------------------------------------------
| ListBox32::unCheck                                                           |
|                                                                              |
| Set an item as unchecked in the list.                                        |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::unCheck(unsigned long index)
{
  check(index, false);
  return( *this );
};

/*------------------------------------------------------------------------------
| ListBox32::isChecked                                                         |
|                                                                              |
| Query whether given item is checked.                                         |
------------------------------------------------------------------------------*/
Boolean ListBox32::isChecked(unsigned long index) const
{
  IEventResult evt = handle().sendEvent(LMX_QUERYCHECK,
                                        IEventParameter1(index-1),
                                        IEventParameter2(0));
  if ((evt.asUnsignedLong() != LIT_NONE) && (evt.asUnsignedLong() == index))
    return( true );
   else
    return( false );
}

/*------------------------------------------------------------------------------
| ListBox32::checkAll                                                          |
|                                                                              |
| Sequentially check all items in list box.                                    |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::checkAll()
{
  int i, j;
  for (i = 0, j = count(); i < j; i++)
    check(i);

  return( *this );
}

/*------------------------------------------------------------------------------
| ListBox32::deselectAll                                                       |
|                                                                              |
| Set all items as unchecked.                                                  |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::unCheckAll()
{
  IEventResult evt = handle().sendEvent(LMX_SETCHECK,
                                        IEventParameter1(LIT_NONE),
                                        IEventParameter2(FALSE));
  if (!(evt.asUnsignedLong()))
    ITHROWGUIERROR("LMX_SETCHECK");

   return( *this );
};

/*------------------------------------------------------------------------------
| ListBox32::numberChecked                                                     |
|                                                                              |
| Return the number of checked items in the list.                              |
------------------------------------------------------------------------------*/
unsigned long ListBox32::numberChecked() const
{
   unsigned long  workSelect, i;
   workSelect = LIT_FIRST;
   i = 0;

   for (i = 0; ((workSelect = handle().sendEvent(LMX_QUERYCHECK,
                                                 IEventParameter1(workSelect),
                                                 IEventParameter2(0)))
                 != LIT_NONE); i++) {;}

   return( i );
};

/*------------------------------------------------------------------------------
| ListBox32::checkedItem                                                       |
|                                                                              |
| Return the index of the first checked item (or LIT_NONE).                    |
------------------------------------------------------------------------------*/
long ListBox32::checkedItem() const
{
  IEventResult evt = handle().sendEvent(LMX_QUERYCHECK,
                                        IEventParameter1(LIT_FIRST),
                                        IEventParameter2(0));
  return( (long)evt.asUnsignedLong() );
};

/*------------------------------------------------------------------------------
| ListBox32::isSound                                                           |
|                                                                              |
| Returns true if sound support is available.                                  |
------------------------------------------------------------------------------*/
Boolean ListBox32::isSound() const
{
  return( this->bSoundSupported );
}

/*------------------------------------------------------------------------------
| ListBox32::soundEvent                                                        |
|                                                                              |
| Returns a wave file name for the event if it is set.                         |
------------------------------------------------------------------------------*/
IString ListBox32::soundEvent(ClickEvent value) const
{
  /***************************************************************/
  /* Throw an exception if sound is not supported on this system */
  /***************************************************************/
  IASSERTSTATE( isSound() == true );

  /***************************************************************/
  /* Get the sound event                                         */
  /***************************************************************/
  unsigned long ulClick = (value == singleClick)  ?  LSND_SINGLECLICK
                                                  :  LSND_DOUBLECLICK;
  IString waveFile = IString( 0, CCHMAXPATH );

  IEventResult evt = handle().sendEvent(LMXM_QUERYSOUNDEVENT,
                                        IEventParameter1(ulClick),
                                        IEventParameter2((char *)waveFile));
  if (!evt.asUnsignedLong());
    ITHROWGUIERROR( "LMXM_QUERYSOUNDEVENT" );

  return( waveFile );
}

/*------------------------------------------------------------------------------
| ListBox32::setSoundEvent                                                     |
|                                                                              |
| Sets a wave file name for the event.                                         |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::setSoundEvent(ClickEvent value, const char *pszWaveFile)
{
  /***************************************************************/
  /* Throw an exception if sound is not supported on this system */
  /***************************************************************/
  IASSERTSTATE( isSound() == true );

  unsigned long ulClick = (value == singleClick)  ?  LSND_SINGLECLICK
                                                  :  LSND_DOUBLECLICK;

  /***************************************************************/
  /* Set the sound event                                         */
  /***************************************************************/
  handle().sendEvent(LMXM_SETSOUNDEVENT,
                     IEventParameter1(ulClick),
                     IEventParameter2((char *)pszWaveFile));
  return( *this );
}

/*------------------------------------------------------------------------------
| ListBox32::isCheckBox                                                        |
------------------------------------------------------------------------------*/
Boolean ListBox32::isCheckBox() const
{
  if (extendedStyle() & LSXS_CHECKBOX)
    return( true );
  else
    return( false );
}

/*------------------------------------------------------------------------------
| ListBox32::enableCheckBox                                                    |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::enableCheckBox(Boolean bTurnOn)
{
  unsigned long ulExtStyle = extendedStyle();
  unsigned long ulOldStyle = ulExtStyle;

  if (bTurnOn)
    ulExtStyle |= LSXS_CHECKBOX;
  else
    ulExtStyle &= ~LSXS_CHECKBOX;

  if (ulOldStyle != ulExtStyle)
  {
    setExtendedStyle(ulExtStyle);
    refresh();
  }
  return( *this );
}

/*------------------------------------------------------------------------------
| ListBox32::disableCheckBox                                                   |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::disableCheckBox()
{
  enableCheckBox(false);
  return( *this );
}

/*------------------------------------------------------------------------------
| ListBox32::defaultExtendedStyle                                              |
------------------------------------------------------------------------------*/
ListBox32::ExtendedStyle ListBox32::defaultExtendedStyle()
{
  return currentDefaultExtendedStyle;
}

/*------------------------------------------------------------------------------
| ListBox32::setDefaultExtendedStyle                                           |
------------------------------------------------------------------------------*/
void ListBox32::setDefaultExtendedStyle(ExtendedStyle extendedStyle)
{
  currentDefaultExtendedStyle = extendedStyle;
}

/*------------------------------------------------------------------------------
| ListBox32::calcMinimumSize                                                   |
|                                                                              |
| Returns the recommended minimum size of the 32-Bit list box control.  The    |
| size is based on the text string length of the longest string (if not using  |
| IListBox::horizontalScroll style) and the current font.                      |
------------------------------------------------------------------------------*/
ISize ListBox32::calcMinimumSize() const
{
  /***************************************************************/
  /* Use default if horizontal scrolling style is set            */
  /***************************************************************/
  if (style() & IListBox::horizontalScroll.asUnsignedLong())
    return( Inherited::calcMinimumSize() );

  /***************************************************************/
  /* Calculate the smallest possible size required to display    */
  /* one item in the list box.                                   */
  /***************************************************************/
  IEventResult evt = handle().sendEvent(LMX_CALCSIZE,
                                        IEventParameter1(1),
                                        IEventParameter2(0));
  return( ISize(evt.lowNumber(), evt.highNumber()) );
}

/*------------------------------------------------------------------------------
| ListBox32::extendedStyle                                                     |
|                                                                              |
| Returns the extended style ...                                               |
------------------------------------------------------------------------------*/
unsigned long ListBox32::extendedStyle( ) const
{
  return( this->ulExtendedStyle );
}

/*------------------------------------------------------------------------------
| ListBox32::setExtendedStyle                                                  |
|                                                                              |
| Set the extended style ...                                                   |
------------------------------------------------------------------------------*/
ListBox32& ListBox32::setExtendedStyle( const unsigned long ulExt )
{
  this->ulExtendedStyle = ulExt;
  return( *this );
}

