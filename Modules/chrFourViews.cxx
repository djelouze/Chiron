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

   pqObjectBuilder* objectBuilder = 0;
   objectBuilder = this->Core->getObjectBuilder( );

   while( viewManager->getActiveView() )
   {
      cerr << "destroying " << viewManager->getActiveView() << endl;
      objectBuilder->destroy( viewManager->getActiveView() );
      cerr << viewManager->getActiveView() <<" destroyed " << endl;
   }

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

   chrContextMenuModifier* cxMenuModifier = new chrContextMenuModifier( );
   cxMenuModifier->SetView( view );   
   
   
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

