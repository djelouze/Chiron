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

#include <algorithm>

chrChangeActiveView::chrChangeActiveView( )
{

}

chrChangeActiveView::~chrChangeActiveView( )
{

}

void chrChangeActiveView::Activate( )
{
   pqViewManager* viewManager = 0;
   viewManager = qobject_cast<pqViewManager*>
                (this->Core->manager("MULTIVIEW_MANAGER"));
   if( !viewManager )
      return;

   // Get the active view
   pqView* activeView = viewManager->getActiveView( );
   if( activeView )
      // Activate the view modules if this view has not already been changed
      if( vtkstd::find(this->changedViews.begin(),
               this->changedViews.end(),
               activeView ) == this->changedViews.end() ) 
         this->activateViewModules( activeView );
}


void chrChangeActiveView::activateViewModules( pqView* view )
{
   chrImageInfoOverlay* imageInfoOverlay = new chrImageInfoOverlay( );
   imageInfoOverlay->SetView( view );
   
   chrSliceVolume* sliceModule = new chrSliceVolume( );
   sliceModule->SetView( view );
   
   chrClickAndSlice* clickAndSliceModule = new chrClickAndSlice( );
   clickAndSliceModule->SetView( view );
   
   chrLandmarkSelector* landmarkModule = new chrLandmarkSelector( );
   landmarkModule->SetView( view );
   
   chrContourTracer* contourModule = new chrContourTracer( );
   contourModule->SetView( view );
   
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
      
      cxMenuModifier->AddContextMenuItemToView( rvbView, "Contour Tracer...",
                                             contourModule ); 
   }   
   
   this->changedViews.push_back( view );
}

void chrChangeActiveView::Deactivate( )
{
//   while( !this->viewModuleCollection.empty( ) )
//   {
//      this->viewModuleCollection.back( )->Deactivate( );
//      this->viewModuleCollection.pop_back( );
//   }
}

