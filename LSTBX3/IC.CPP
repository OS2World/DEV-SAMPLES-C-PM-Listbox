//------------------------------------------------------------------------------
//
// Sample Direct Manipulation program
//
//------------------------------------------------------------------------------
//
// This program demonstrates the ability to drag/drop between the entry fields
// and the list box, but not the combination box.
//
//------------------------------------------------------------------------------
extern "C"
{
  #define INCL_WINSYS
  #define INCL_WINLISTBOXES
  #include <os2.h>
}
#include <iapp.hpp>
#include <icolor.hpp>

#include "ic.hpp"
#include "ic.h"
#include "listbox.h"

void main()
{
  DemoWindow mainWindow( IC_MAIN );
  IApplication::current().run();
}

/*------------------------------------------------------------------------------
| ListBox32::ListBox32                                                         |
|                                                                              |
| Construct a ListBox32 on an IWindow.                                         |
------------------------------------------------------------------------------*/
DemoWindow::DemoWindow( unsigned long ulId )
           : IFrameWindow( IFrameWindow::defaultStyle(), ulId ),
             ICommandHandler(),
             ISelectHandler(),
             clientCanvas( IC_CLIENT, this, this ),
             titleText( IC_TITLE, &clientCanvas, &clientCanvas ),
             soundCanvas( IC_SOUNDCANVAS, &clientCanvas, &clientCanvas ),
             soundBox( IC_SOUNDBOX, &soundCanvas, &soundCanvas ),
             chkAllButton( IC_CHECKALL, &clientCanvas, &clientCanvas ),
             unChkAllButton( IC_UNCHECKALL, &clientCanvas, &clientCanvas ),
             selAllButton( IC_SELECTALL, &clientCanvas, &clientCanvas ),
             deSelAllButton( IC_DESELECTALL, &clientCanvas, &clientCanvas )
{
  /***************************************************************/
  /* Multicell canvas is the client                              */
  /***************************************************************/
  setClient( &clientCanvas );

  ICommandHandler::handleEventsFor( this );
  ISelectHandler::handleEventsFor( &soundBox );

  /***************************************************************/
  /* Create the 32-Bit replacement list box                      */
  /***************************************************************/
  pListBox = new ListBox32( IC_LISTBOX,
                            &clientCanvas,
                            &clientCanvas,
                            IRectangle( 10,10,100,175 ),
                            IWindow::visible |
                                  IListBox::horizontalScroll |
                                  IListBox::extendedSelect,
                            ListBox32::checkBox );

  /***************************************************************/
  /* Add entries into the listbox                                */
  /***************************************************************/
  pListBox->addAsLast( "animal"   );
  pListBox->addAsLast( "bear"     );
  pListBox->addAsLast( "camel"    );
  pListBox->addAsLast( "donkey"   );
  pListBox->addAsLast( "elephanttttttttttttttttttttttttttttttt" );
  pListBox->addAsLast( "fox"      );
  pListBox->addAsLast( "gopher"   );
  pListBox->addAsLast( "hound"    );
  pListBox->addAsLast( "iguana"   );
  pListBox->addAsLast( "jackal"   );

  pListBox->select( 0 );

  /***************************************************************/
  /* Set the background color                                    */
  /***************************************************************/
  pListBox->setColor( IListBox::background, IColor::cyan );

  /***************************************************************/
  /* Init list box title                                         */
  /***************************************************************/
  titleText.setAlignment( IStaticText::centerCenter );
  titleText.setText( "32-Bit Replacement List box" );

  /***************************************************************/
  /* Sound enablement                                            */
  /***************************************************************/
  soundBox.setText( "Sound" );
  soundCanvas.addToCell( &soundBox, 2, 1 );
  soundCanvas.setColumnWidth( 1, 1, true );
  soundCanvas.setColumnWidth( 3, 1, true );
  if (!pListBox->isSound())
    soundBox.disable();

  /***************************************************************/
  /* Init push buttons                                           */
  /***************************************************************/
  chkAllButton.setText( "Check All" );
  unChkAllButton.setText( "Uncheck All" );
  selAllButton.setText( "Select All" );
  deSelAllButton.setText( "Deselect All" );
  unChkAllButton.disable();
  deSelAllButton.disable();

  /***************************************************************/
  /* Set tabstop and group styles                                */
  /***************************************************************/
  chkAllButton.enableGroup().enableTabStop();

  clientCanvas.addToCell( &titleText, 3, 2 );
  clientCanvas.addToCell( pListBox, 3, 4 );
  clientCanvas.addToCell( &soundCanvas, 3, 6 );
  clientCanvas.addToCell( &chkAllButton, 2, 7 );
  clientCanvas.addToCell( &selAllButton, 4, 7 );
  clientCanvas.addToCell( &unChkAllButton, 2, 8 );
  clientCanvas.addToCell( &deSelAllButton, 4, 8 );

  clientCanvas.setRowHeight( 1, 5 );
  clientCanvas.setRowHeight( 3, 10 );
  clientCanvas.setRowHeight( 5, 15 );
  clientCanvas.setColumnWidth( 1, 10 );

  setDestroyOnClose( true );
  pListBox->setFocus();
  show();
}

DemoWindow::~DemoWindow( )
{
}

Boolean DemoWindow::command( ICommandEvent &evt )
{
  Boolean fProcessed;

  switch(evt.commandId())
  {
    case IC_CHECKALL:
    {
      long lCount =
          pListBox->sendEvent( LMX_QUERYITEMCOUNT, 0, 0 );
      if ( lCount != LIT_NONE )
      {
        long i;
        for (i=0; i < lCount; i++)
          evt.setResult( pListBox->sendEvent( LMX_SETCHECK, (int)i, 0 ) );
      }
      chkAllButton.disable();
      unChkAllButton.enable();
      fProcessed = true;
      break;
    }

    case IC_UNCHECKALL:
      evt.setResult( pListBox->sendEvent( LMX_SETCHECK, LIT_NONE, 0 ) );
      unChkAllButton.disable();
      chkAllButton.enable();
      fProcessed = true;
      break;

    case IC_SELECTALL:
      evt.setResult( pListBox->sendEvent( LMX_SELECTALL, 0, 0 ) );
      selAllButton.disable();
      deSelAllButton.enable();
      fProcessed = true;
      break;

    case IC_DESELECTALL:
      evt.setResult( pListBox->sendEvent( LM_SELECTITEM, LIT_NONE, 0 ) );
      deSelAllButton.disable();
      selAllButton.enable();
      fProcessed = true;
      break;

    default:
      fProcessed = false;
      break;
  }

  return( fProcessed );
}

Boolean DemoWindow::selected( IControlEvent &evt )
{
  if (evt.controlId() == IC_SOUNDBOX)
  {
    /*************************************************************/
    /* Test selection state and set the sound event if selected. */
    /* Note that there is no current way to disable the sound    */
    /* once it is set.  However, you can modify the              */
    /* LMXM_SETSOUNDEVENT api to allow you to disable the sound, */
    /* making the appropriate modifications here as well.        */
    /*************************************************************/
    if (soundBox.isSelected())
      pListBox->setSoundEvent( ListBox32::singleClick, "ahooga.wav" );

    return( true );
  }

  return( false );
}

