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

// Chiron includes
#include "chrSliceVolume.h"
#include "chrWindowLevel.h"
#include "chrImageInfoOverlay.h"
#include "chrScaleInfoOverlay.h"
#include "chrGenericLayout.h"

// QT includes
#include <QObject>

// ParaView includes
#include "pqApplicationCore.h"
#include "pqObjectBuilder.h"

//-----------------------------------------------------------------------------
ChironToolbarActions::ChironToolbarActions(QObject* p) : QActionGroup(p)
{
   // First Chiron toolbar button is checkable, but not exclusive
   this->setExclusive( false );

   // Adding buttons (ie actions) to the plugin's toolbar
   QAction* a;
   // Define a new action : Icon, tool tip and parent
   a = new QAction( QIcon(":/ToolbarIcons/chiron-256x256.png"), 
                    "Enable Chiron", 
                    this );
   a->setCheckable( true );
   
   // setData give the possibility to determine which button has been pressed
   a->setData("EnableChiron");

   // Add this action to the action group, ie the toolbar
   this->addAction(a);

   // New actions will be added here (property panels,...)
   // BEGIN NEW ACTIONS
 
   // END NEW ACTIONS   

   // Connect the signal triggered by the toolbar 
   // to the slot (ie function) onAction. 'triggered' 
   // is a signal sent when one of the toolbar button is pressed
   QObject::connect(this, SIGNAL(triggered(QAction*)), 
                    this, SLOT(onAction(QAction*)));
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

   // Main activation button
   //   - activate/deactivate existing modules
   //   - connect to the viewCreated signal in order to 
   //     perform asynchronous activations
   if( actionStr == QString( "EnableChiron") )
   {
      // When Chiron is enabled, view creations are detected and connected
      // to each module
      this->connectToViewCreation( a->isChecked( ));
      if( a->isChecked( ) )
      {
         //! \todo loop over viewModuleList to activate them
      }
      else
      {
         //! \todo loop over viewModuleList to deactivate them
      }
   }
}

void ChironToolbarActions::connectToViewCreation( bool connect )
{
   pqApplicationCore* core = pqApplicationCore::instance();
   pqObjectBuilder* builder = core->getObjectBuilder();

   chrGenericLayout* layoutModule = new chrGenericLayout();
   layoutModule->Activate( );

   if( 0 )//connect )
   {
      QObject::connect(builder, 
                       SIGNAL(viewCreated(pqView*)),
                       this,
                       SLOT(connectToChironModules(pqView*)));
   }
   else
   {
      QObject::disconnect(builder, 
                          SIGNAL(viewCreated(pqView*)), 
                          this,
                          SLOT(connectToChironModules(pqView*)));

   }
}


void ChironToolbarActions::connectToChironModules( pqView* view )
{
   chrSliceVolume* moduleSlice = new chrSliceVolume( );
   moduleSlice->SetView( view );
   moduleSlice->Activate( );

   chrWindowLevel* moduleWL = new chrWindowLevel( );
   moduleWL->SetView( view );
   moduleWL->Activate( );


   chrImageInfoOverlay* moduleOverlay = new chrImageInfoOverlay( );
   moduleOverlay->SetView( view );
   moduleOverlay->Activate( );
   this->viewModuleList.push_back( moduleOverlay );
 
   chrScaleInfoOverlay* moduleScaleOverlay = new chrScaleInfoOverlay();
   moduleScaleOverlay->SetView( view );
   moduleScaleOverlay->Activate( );
}



