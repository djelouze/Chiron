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
 
#include "chrChangeActiveView.h"

chrChangeActiveView::chrChangeActiveView( )
{

}

chrChangeActiveView::~chrChangeActiveView( )
{

}

void chrChangeActiveView::Activate( )
{
   pqViewManager * viewManager = qobject_cast<pqViewManager*>
                (this->Core->manager("MULTIVIEW_MANAGER"));
   pqView* activeView = viewManager->getActiveView( );
   if( activeView )
      this->activateViewModules( activeView );
}


void chrChangeActiveView::activateViewModules( pqView* view )
{
   chrImageInfoOverlay* imageInfoOverlay = new chrImageInfoOverlay( );
   imageInfoOverlay->SetView( view );
//   imageInfoOverlay->Activate( );
   
   chrSliceVolume* sliceModule = new chrSliceVolume( );
   sliceModule->SetView( view );
   sliceModule->ButtonActivate( );
   
   chrClickAndSlice* clickAndSliceModule = new chrClickAndSlice( );
   clickAndSliceModule->SetView( view );
   clickAndSliceModule->ButtonActivate( );
   
   chrScaleInfoOverlay* scaleInfoOverlay = new chrScaleInfoOverlay( );
   scaleInfoOverlay->SetView( view );
   scaleInfoOverlay->Activate( );
   
   this->viewModuleCollection.push_back( sliceModule );
   this->viewModuleCollection.push_back( scaleInfoOverlay );
   this->viewModuleCollection.push_back( imageInfoOverlay );
}

void chrChangeActiveView::Deactivate( )
{
//   while( !this->viewModuleCollection.empty( ) )
//   {
//      this->viewModuleCollection.back( )->Deactivate( );
//      this->viewModuleCollection.pop_back( );
//   }
}

