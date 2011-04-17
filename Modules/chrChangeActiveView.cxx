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
         this->linkModulesToView( activeView );
}


void chrChangeActiveView::linkModulesToView( pqView* view )
{
   chrImageInfoOverlay* imageInfoOverlay = new chrImageInfoOverlay( );
   imageInfoOverlay->SetView( view );
 
   chrWindowLevel* windowLevel = new chrWindowLevel( );
   windowLevel->SetView( view );
   
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

   chrContextMenuModifier* cxMenuModifier = new chrContextMenuModifier( );
   cxMenuModifier->SetView( view );
   cxMenuModifier->AddContextMenuItemToView( imageInfoOverlay,  
                                             "Image Information...");
   cxMenuModifier->AddContextMenuItemToView( windowLevel,
                                             "Window/Level...");
   cxMenuModifier->AddContextMenuItemToView( sliceModule,
                                             "Slice Volume...");
   cxMenuModifier->AddContextMenuItemToView( landmarkModule,
                                             "Landmark Selector...");
   cxMenuModifier->AddContextMenuItemToView( contourModule,
                                             "Contour Tracer...");
   cxMenuModifier->AddContextMenuItemToView( scaleInfoOverlay,
                                             "Rules...");   
   
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

