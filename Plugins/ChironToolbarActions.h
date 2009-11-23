//! \class ChironToolbarActions
//! \brief Main entry for the Chiron ParaView plugin
//!
//! As soon as the Chiron plugin loads, this toolbar is created in ParaView.
//! Chiron toolbar has -for now- 1 button:
//!    - Enable Chiron
//!      When future views are created, Chiron modules are connected to
//!      them and play their role (event catching, overlay conf., ...)
//!
//! \todo Implements Chiron abstract module
//! \bug In release mode, QVTKWidget crashes ParaView when manipulating its
//! interactor. \see http://public.kitware.com/Bug/view.php?id=9895
//!
//! \author Jerome Velut
//! \date 07 november 2009

#ifndef __CHIRONTOOLBARACTIONS_H__
#define __CHIRONTOOLBARACTIONS_H__

// Chiron includes
#include "chrViewModule.h"

// QT includes
#include <QActionGroup>

// ParaView includes
#include <pqView.h>

class ChironToolbarActions : public QActionGroup
{
  Q_OBJECT
public:
  //! Constructor: Defines Qt Slot/Signal connection
  ChironToolbarActions(QObject* p);
  //! Destructor:
  //!    - free the viewModuleList
  virtual ~ChironToolbarActions( );

protected slots:
  //! Callback for each action triggerred.
  //! This function is called after a click on a button of the toolBar
  void onAction(QAction* a);
  void connectToChironModules( pqView* );

private:
   void connectToViewCreation( bool on );
   std::vector<chrViewModule*> viewModuleList;
};

#endif //__CHIRONTOOLBARACTIONS_H__

