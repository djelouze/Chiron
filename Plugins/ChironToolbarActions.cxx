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
 
#include "ChironToolbarActions.h"

// QT includes
#include <QObject>

// ParaView includes
#include "pqApplicationCore.h"
#include "pqObjectBuilder.h"

//-----------------------------------------------------------------------------
ChironToolbarActions::ChironToolbarActions(QObject* p) : QActionGroup(p)
{
   // Adding buttons (ie actions) to the plugin's toolbar
   QAction* changeActiveViewAction;
   // Define a new action : Icon, tool tip and parent
   changeActiveViewAction = new QAction( QIcon(":/ToolbarIcons/chiron-256x256.png"), 
                    "Attach modules to active view", 
                    this );
   // setData give the possibility to determine which button has been pressed
   changeActiveViewAction->setData("ChangeActiveView");
   // Add this action to the action group, ie the toolbar
   this->addAction( changeActiveViewAction );

   // New actions will be added here (property panels,...)
   // BEGIN NEW ACTIONS
   
   // FourViews is not ready: don't add it to the toolbar now
   QAction* fourViewsAction;
//   fourViewsAction =  new QAction( QIcon(":/ToolbarIcons/chiron-256x256.png"), 
//                    "Build four views", 
//                    this );
//   fourViewsAction->setData("FourViews");
//   this->addAction( fourViewsAction );
 
   // END NEW ACTIONS   

   // Connect the signal triggered by the toolbar 
   // to the slot (ie function) onAction. 'triggered' 
   // is a signal sent when one of the toolbar button is pressed
   QObject::connect(this, SIGNAL(triggered(QAction*)), 
                    this, SLOT(onAction(QAction*)));

  // Instanciate the generic layout module
  this->changeActiveViewModule = new chrChangeActiveView( );
  this->fourViewsBuilder = new chrFourViews( );
}

ChironToolbarActions::~ChironToolbarActions()
{
   while( !this->viewModuleList.empty( ) )
      this->viewModuleList.pop_back( );
}

//-----------------------------------------------------------------------------
void ChironToolbarActions::onAction(QAction* a)
{
   QString actionStr = a->data().toString();

   // Perform activation according to the pressed button
   if( actionStr == QString( "ChangeActiveView") )
   {
      this->changeActiveViewModule->Activate( );
   }
   if( actionStr == QString( "FourViews") )
   {
      this->fourViewsBuilder->Activate( );
   }

}



