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
   //QAction* fourViewsAction;
   //fourViewsAction =  new QAction( QIcon(":/ToolbarIcons/chiron-256x256.png"), 
   //                 "Build four views", 
   //                 this );
   //fourViewsAction->setData("FourViews");
   //this->addAction( fourViewsAction );
 
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



