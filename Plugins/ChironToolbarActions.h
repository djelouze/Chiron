// Copyright (c) 2010, Jérôme Velut
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER ``AS IS'' AND ANY EXPRESS 
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN 
// NO EVENT SHALL THE COPYRIGHT OWNER BE LIABLE FOR ANY DIRECT, INDIRECT, 
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
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
#include "chrFourViews.h"

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

private:
   std::vector<chrViewModule*> viewModuleList;
   chrChangeActiveView* changeActiveViewModule;
   chrFourViews* fourViewsBuilder;
};

#endif //__CHIRONTOOLBARACTIONS_H__

