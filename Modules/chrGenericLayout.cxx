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
 
#include "chrGenericLayout.h"

chrGenericLayout::chrGenericLayout( )
{

}

chrGenericLayout::~chrGenericLayout( )
{

}

void chrGenericLayout::Activate( )
{
   pqObjectBuilder* builder = this->Core->getObjectBuilder();
   pqServerManagerModel* smm = this->Core->getServerManagerModel();

   QObject::connect(builder, SIGNAL(viewCreated(pqView*)),
                    this,SLOT(activateViewModules(pqView*)));

   QList<pqServer*> serversList;
   serversList = smm->findItems<pqServer*>( );

   // PoC code: create views on the first server found
   if( serversList.count() != 0 )
      this->createViews( serversList[0] );
   else
      cerr << "No server found..."<< endl;


}

void chrGenericLayout::createViews( pqServer* server )
{
   // By default, ParaView create a render view. Remove it.
   pqViewManager * viewManager = qobject_cast<pqViewManager*>
                (this->Core->manager("MULTIVIEW_MANAGER"));
   viewManager->removeWidget( viewManager->getFrame(viewManager->getActiveView( )));
   // The objectBuilder make the view factory available
   pqObjectBuilder* builder = this->Core->getObjectBuilder();

   // Create the four views
   this->xzView = builder->createView( "RenderView", server );
   pqRenderView* renderView = qobject_cast<pqRenderView*>(this->xzView);
   renderView->setCenterAxesVisibility( false );
   renderView->getRenderViewProxy()
         ->GetActiveCamera()
         ->SetParallelProjection( 1 );

   viewManager->getFrame( this->xzView )->splitVertical();

   this->xyView = builder->createView( "RenderView", server );
   renderView = qobject_cast<pqRenderView*>(this->xyView);
   renderView->setCenterAxesVisibility( false );
   renderView->getRenderViewProxy()
         ->GetActiveCamera()
         ->SetParallelProjection( 1 );

   this->yzView = builder->createView( "RenderView", server );
   renderView = qobject_cast<pqRenderView*>(this->yzView);
   renderView->setCenterAxesVisibility( false );
   renderView->getRenderViewProxy()
         ->GetActiveCamera()
         ->SetParallelProjection( 1 );

   viewManager->getFrame( this->xzView )->splitHorizontal( );

   this->threeDView = builder->createView( "RenderView", server );
   renderView = qobject_cast<pqRenderView*>(this->threeDView);
   renderView->setCenterAxesVisibility( false );
   renderView->getRenderViewProxy()
         ->GetActiveCamera()
         ->SetParallelProjection( 0 );
   this->resetViewDirection();
}

void chrGenericLayout::resetViewDirection( )
{
   qobject_cast<pqRenderView*>(xzView)->resetViewDirection( 0,0,-1,0,-1,0);
   qobject_cast<pqRenderView*>(xyView)->resetViewDirection( 1,0,0,0,0,1);
   qobject_cast<pqRenderView*>(yzView)->resetViewDirection( 0,-1,0,0,0,1);
}


void chrGenericLayout::activateViewModules( pqView* view )
{
   chrSliceVolume* sliceModule = new chrSliceVolume( );
   sliceModule->SetView( view );
   sliceModule->Activate( );
   
   chrScaleInfoOverlay* scaleInfoOverlay = new chrScaleInfoOverlay( );
   scaleInfoOverlay->SetView( view );
   scaleInfoOverlay->Activate( );
   
   chrImageInfoOverlay* imageInfoOverlay = new chrImageInfoOverlay( );
   imageInfoOverlay->SetView( view );
   imageInfoOverlay->Activate( );
   
   this->viewModuleCollection.push_back( sliceModule );
   this->viewModuleCollection.push_back( scaleInfoOverlay );
   this->viewModuleCollection.push_back( imageInfoOverlay );
}

void chrGenericLayout::Deactivate( )
{
   pqObjectBuilder* builder = this->Core->getObjectBuilder();
   QObject::disconnect(builder, SIGNAL(viewCreated(pqView*)),
                    this,SLOT(activateViewModules(pqView*)));

//   while( !this->viewModuleCollection.empty( ) )
//   {
//      this->viewModuleCollection.back( )->Deactivate( );
//      this->viewModuleCollection.pop_back( );
//   }
}

