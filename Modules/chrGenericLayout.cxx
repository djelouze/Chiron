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
}
