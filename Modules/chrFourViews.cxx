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

