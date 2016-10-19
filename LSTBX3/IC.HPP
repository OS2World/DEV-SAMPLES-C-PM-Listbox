#ifndef IC_HPP
  #define IC_PP

#include <iframe.hpp>                   // IFrameWindow
#include <istattxt.hpp>                 // IStaticText
#include <ipushbut.hpp>                 // IPushButton
#include <icheckbx.hpp>                 // ICheckBox
#include <imcelcv.hpp>                  // IMultiCellCanvas
#include <icmdhdr.hpp>                  // ICommandHandler
#include <ictlevt.hpp>                  // IControlEvent
#include <iselhdr.hpp>                  // ISelectHandler

#include "xlistbox.hpp"


/******************************************************************************/
/* Class   : AMultiCellCanvas                                                 */
/*                                                                            */
/* Purpose : main window for multi cell canvas sample application             */
/*           the window contains a multi-cell canvas and the other controls   */
/*           are attached to the canvas.  The pushbutton displays a           */
/*           message box showing the current state of the buttons             */
/*           AMultiCellCanvas is derived from IFrameWindow                    */
/******************************************************************************/
class DemoWindow : public IFrameWindow, public ICommandHandler,
                                        public ISelectHandler
{
typedef IFrameWindow
  Inherited;

public:
  DemoWindow   ( unsigned long windowId );
  ~DemoWindow  ( );

protected:
Boolean
  command      ( ICommandEvent &event ),
  selected     ( IControlEvent &event );

private:
IMultiCellCanvas
  clientCanvas;

ListBox32
 *pListBox;

IStaticText
  titleText;

IMultiCellCanvas
  soundCanvas;
ICheckBox
  soundBox;

IPushButton
  chkAllButton,
  unChkAllButton,
  selAllButton,
  deSelAllButton;
};

#endif
