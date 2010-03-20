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
 
#include "chrFourViews.h"

chrFourViews::chrFourViews( )
{

}

chrFourViews::~chrFourViews( )
{

}

void chrFourViews::Activate( )
{
   pqViewManager * viewManager = 0;
   viewManager = qobject_cast<pqViewManager*>
                (this->Core->manager("MULTIVIEW_MANAGER"));
   if( !viewManager )
      return;

   // BUGGY: viewManager->reset( );
   pqView* activeView = 0;
   for( int widgetId = 0; widgetId < viewManager->count( ); widgetId++ )
   {
      pqMultiViewFrame* mvFrame = static_cast<pqMultiViewFrame*>(viewManager->widget( widgetId ));
      cout << "removing widget " << mvFrame << endl;
      if( mvFrame )
         mvFrame->close( );
   }
//   do{
//   activeView = viewManager->getActiveView( );
//   viewManager->getFrame( activeView )->close( );
//   } while( activeView ); 
//   if( activeView )
//      this->activateViewModules( activeView );
}


void chrFourViews::activateViewModules( pqView* view )
{
   chrImageInfoOverlay* imageInfoOverlay = new chrImageInfoOverlay( );
   imageInfoOverlay->SetView( view );
   
   chrSliceVolume* sliceModule = new chrSliceVolume( );
   sliceModule->SetView( view );
   
   chrClickAndSlice* clickAndSliceModule = new chrClickAndSlice( );
   clickAndSliceModule->SetView( view );
   
   chrLandmarkSelector* landmarkModule = new chrLandmarkSelector( );
   landmarkModule->SetView( view );
   
   chrScaleInfoOverlay* scaleInfoOverlay = new chrScaleInfoOverlay( );
   scaleInfoOverlay->SetView( view );
   scaleInfoOverlay->Activate( );

   pqRenderViewBase* rvbView = 0;
   rvbView = static_cast<pqRenderViewBase*>(view);
   if( rvbView )
   {
      chrContextMenuModifier* cxMenuModifier = new chrContextMenuModifier( );
      cxMenuModifier->AddContextMenuItemToView( rvbView, "Image Information...",
                                             imageInfoOverlay ); 
   
      cxMenuModifier->AddContextMenuItemToView( rvbView, "Slice Volume...",
                                             sliceModule ); 
   
      cxMenuModifier->AddContextMenuItemToView( rvbView, "Landmark Selector...",
                                             landmarkModule ); 
   }   
   
   this->viewModuleCollection.push_back( sliceModule );
   this->viewModuleCollection.push_back( scaleInfoOverlay );
   this->viewModuleCollection.push_back( imageInfoOverlay );
}

void chrFourViews::Deactivate( )
{
//   while( !this->viewModuleCollection.empty( ) )
//   {
//      this->viewModuleCollection.back( )->Deactivate( );
//      this->viewModuleCollection.pop_back( );
//   }
}

