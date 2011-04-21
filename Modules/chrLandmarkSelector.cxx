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
 
#include "chrLandmarkSelector.h"

// ParaView includes
#include "pqDataRepresentation.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMProxy.h"

chrLandmarkSelector::chrLandmarkSelector( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
}


chrLandmarkSelector::~chrLandmarkSelector( )
{
   this->EventConnect->Delete( );
}


void chrLandmarkSelector::Activate( )
{
   if( this->GetView() && !this->Activated )
   {
      this->toggleMode( );
   }
}

void chrLandmarkSelector::Deactivate( )
{
   if( this->GetView() && this->Activated )
      this->toggleMode( );
}

void chrLandmarkSelector::toggleMode( )
{
   if( !this->Activated )
   {
       this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::LeftButtonPressEvent,
                                  this,
                                  SLOT(leftButtonPress( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);

     this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::LeftButtonReleaseEvent,
                                  this,
                                  SLOT(leftButtonRelease( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);

       this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::KeyPressEvent,
                                  this,
                                  SLOT(keyPress( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);

      this->Activated = 1;
      this->PointSourceProxies.empty( );
   }
   else
   {
      this->EventConnect->Disconnect( ); 
      this->Activated = 0;
   }
}

void chrLandmarkSelector::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   if( this->GetRenderWindowInteractor( )->GetShiftKey( ) )
      command->AbortFlagOn();
}

void chrLandmarkSelector::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   if( this->GetRenderWindowInteractor( )->GetShiftKey( ) )
   {
      command->AbortFlagOn();
      this->InsertPoint( );
   }
}

void chrLandmarkSelector::keyPress(vtkObject * obj, unsigned long,
                              void * client_data, void *,
                              vtkCommand * command)
{
   command->AbortFlagOn();
   if( this->GetRenderWindowInteractor( )->GetKeyCode() == 'a' ) // Set the points list as a ChainSource
   {
      this->AppendPointSources( );
   }
}

void chrLandmarkSelector::AppendPointSources( )
{
   cout << "Append point sources: not implemented" << endl;
}

void chrLandmarkSelector::InsertPoint( )
{
   int* position = this->GetRenderWindowInteractor( )->GetEventPosition();
      
   vtkPointPicker* picker = vtkPointPicker::New( );
   picker->Pick( position[0], position[1], 0, this->GetRenderer() );
   vtkPoints* pickedPositions = picker->GetPickedPositions( );

   int i;
   double point[3];
   for( i = 0; i < pickedPositions->GetNumberOfPoints( ) ; i++)
   {
      pickedPositions->GetPoint( i, point );
   }

   pqObjectBuilder* builder = pqApplicationCore::instance()->getObjectBuilder();
   pqServerManagerModel* smm = pqApplicationCore::instance()->getServerManagerModel();
   pqViewManager * viewManager = qobject_cast<pqViewManager*>
                 (pqApplicationCore::instance()->manager("MULTIVIEW_MANAGER"));

   QList<pqServer*> serversList = smm->findItems<pqServer*>( );

   if( serversList.count() != 0 )
   {
      pqPipelineSource* pipelineSource = 0;
      pipelineSource = builder->createSource( "sources",
                                              "PointSource",
                                              serversList[0] );
      this->PointSourceProxies.push_back( pipelineSource );
      
      if( pipelineSource )
      {
         vtkSMProxy* proxy = 0;
         proxy = pipelineSource->getProxy();
         if( proxy )
         {
            vtkSMDoubleVectorProperty* centerProperty = 0;
            centerProperty = static_cast<vtkSMDoubleVectorProperty*>(proxy->GetProperty( "Center" ));
            if( centerProperty )
            {
               centerProperty->SetElement( 0, point[0] );
               centerProperty->SetElement( 1, point[1] );
               centerProperty->SetElement( 2, point[2] );
            }
            proxy->UpdateSelfAndAllInputs( );
            pqRepresentation* rep = 0;
            rep = builder->createDataRepresentation( pipelineSource->getOutputPort( 0 ), this->GetView( ) );
            rep->setVisible( true );
            this->Core->render( );
            pipelineSource->setModifiedState( pqProxy::UNMODIFIED );

            vtkSMIntVectorProperty* pickable = 0;
            pickable = static_cast<vtkSMIntVectorProperty*>(rep->getProxy()->GetProperty( "Pickable" ));
            if( pickable )
            {
               pickable->SetElement( 0, 0 );
               rep->getProxy()->UpdateProperty( "Pickable" );
            }
         } 
      }
   }
}




int chrLandmarkSelector::IsViewValid( pqView* view )
{
   pqRenderView* renderView = qobject_cast<pqRenderView*>(view);
   if( renderView )
      return( 1 );
   else
      return( 0 );
}


