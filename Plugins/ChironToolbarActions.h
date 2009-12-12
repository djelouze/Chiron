//    Copyright Jerome Velut 2009
//
//    This file is part of Chiron.
//
//    Chiron is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Chiron is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You have received a copy of the GNU General Public License
//    along with Chiron in the file COPYING.  
//    If not, see <http://www.gnu.org/licenses/>.
 
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
#include "chrChangeActiveView.h"

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
   chrChangeActiveView* changeActiveViewModule;
};

#endif //__CHIRONTOOLBARACTIONS_H__

