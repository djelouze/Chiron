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
 
#include "chrLandmarkSelector.h"

// ParaView includes
#include "pqDataRepresentation.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMProxy.h"

chrLandmarkSelector::chrLandmarkSelector( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );

   this->LandmarkPoints = vtkPoints::New( );
   this->LandmarkVertices = vtkCellArray::New( );
   this->LandmarkPolyData = vtkPolyData::New( );

   this->LandmarkPolyData->SetPoints( this->LandmarkPoints );
   this->LandmarkPolyData->SetVerts( this->LandmarkVertices );

   // temporary visualisation pipeline
   this->LandmarkMapper = vtkPolyDataMapper::New( );
   this->LandmarkActor = vtkActor::New( );

   this->LandmarkMapper->SetInput( this->LandmarkPolyData );
   this->LandmarkActor->SetMapper( this->LandmarkMapper );
   this->LandmarkActor->SetPickable( 0 );
   this->LandmarkActor->GetProperty()->SetPointSize( 3 );
}


chrLandmarkSelector::~chrLandmarkSelector( )
{
   this->EventConnect->Delete( );
   this->LandmarkPoints->Delete( );
   this->LandmarkPolyData->Delete( );
   this->LandmarkVertices->Delete( );
}


void chrLandmarkSelector::Activate( )
{
   if( this->GetView() )
   {
      this->toggleMode( );
   }
}

void chrLandmarkSelector::Deactivate( )
{
   if( this->GetView() )
      this->toggleMode( );
}

void chrLandmarkSelector::toggleMode( )
{
   if( !this->Activated )
   {
      this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::MouseWheelBackwardEvent,
                                  this,
                                  SLOT(sliceDown( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);
      this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::MouseWheelForwardEvent,
                                  this,
                                  SLOT(sliceUp( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);
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
      this->GetRenderer( )->AddActor( this->LandmarkActor );
   }
   else
   {
      this->EventConnect->Disconnect( ); 
      this->Activated = 0;
      this->GetRenderer( )->RemoveActor( this->LandmarkActor );
   }
}

void chrLandmarkSelector::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
}

void chrLandmarkSelector::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->InsertPoint( );
}

void chrLandmarkSelector::keyPress(vtkObject * obj, unsigned long,
                              void * client_data, void *,
                              vtkCommand * command)
{
   command->AbortFlagOn();
   if( this->GetRenderWindowInteractor( )->GetKeyCode() == 'r' ) // Set the points list as a ChainSource
   {
      this->BuildChainSource( );
   }
}


void chrLandmarkSelector::sliceDown( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   if( this->GetRenderWindowInteractor()->GetShiftKey() )
      this->ChangeSlice( -10 );
   else
      this->ChangeSlice( -1 );
}

void chrLandmarkSelector::sliceUp( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   if( this->GetRenderWindowInteractor()->GetShiftKey() )
      this->ChangeSlice( 10 );
   else
      this->ChangeSlice( 1 );
}

void chrLandmarkSelector::ChangeSlice( int inc )
{
   QList<pqRepresentation*> repList;
   repList = this->GetView( )->getRepresentations( );

   int i = 0;
   for( i = 0; i < repList.count();i ++)
   {
      pqDataRepresentation* imageSlice = 0;
      imageSlice = static_cast<pqDataRepresentation*>(repList[i]);
      if( imageSlice )
      {
         if( imageSlice->isVisible( ) )
         {
            vtkSMIntVectorProperty* ivp = 0;
            ivp = vtkSMIntVectorProperty::SafeDownCast( imageSlice->getProxy()
                  ->GetProperty("Slice"));
            if( ivp )
            {
               int currentSlice = ivp->GetElement( 0 );

               ivp->SetElement(0, currentSlice + inc);

               imageSlice->getProxy()->UpdateVTKObjects();
               imageSlice->renderView(true);
            }
         }
      }
   }

}

void chrLandmarkSelector::BuildChainSource( )
{
   // The objectBuilder make the view factory available
      pqObjectBuilder* builder = pqApplicationCore::instance()->getObjectBuilder();
      pqServerManagerModel* smm = pqApplicationCore::instance()->getServerManagerModel();
      pqViewManager * viewManager = qobject_cast<pqViewManager*>
         (pqApplicationCore::instance()->manager("MULTIVIEW_MANAGER"));
   
      QList<pqServer*> serversList = smm->findItems<pqServer*>( );

      if( serversList.count() != 0 )
      {
         pqPipelineSource* pipelineSource = 0;
         pipelineSource = builder->createSource( "sources", 
                                                 "ChainSource", 
                                                 serversList[0] );
         if( pipelineSource )
         {
            vtkChainSource* objChainSource = 0;
            objChainSource = static_cast<vtkChainSource*>(pipelineSource->getProxy()->GetClientSideObject());
            if( objChainSource)
            {
               objChainSource->SetPoints( this->LandmarkPoints );
               objChainSource->SetCellTypeToVertices( );
               objChainSource->Update( );
               
               pipelineSource->getProxy()->UpdateSelfAndAllInputs();
               viewManager->getActiveView()->getRepresentation(0)->renderView(true);

               this->LandmarkPoints->Reset( );
               this->LandmarkVertices->Reset( );
            }
         }
      }  
}


void chrLandmarkSelector::InsertPoint( )
{
   int* position = this->GetRenderWindowInteractor( )->GetEventPosition();
      
   vtkPointPicker* picker = vtkPointPicker::New( );
   picker->Pick( position[0], position[1], 0, this->GetRenderer() );
   vtkPoints* pickedPositions = picker->GetPickedPositions( );

   if( this->LandmarkVertices->GetNumberOfCells( ) == 0 )
      this->LandmarkVertices->InsertNextCell( 0 );
   
   int i;
   for( i = 0; i < pickedPositions->GetNumberOfPoints( ) ; i++)
   {
      double point[3];
      pickedPositions->GetPoint( i, point );
      vtkIdType ptId = this->LandmarkPoints->InsertNextPoint( point );
      this->LandmarkVertices->InsertCellPoint( ptId );
      this->LandmarkVertices->UpdateCellCount( this->LandmarkPoints->GetNumberOfPoints( ));
   }
   this->LandmarkPolyData->Modified( );
   this->GetRenderWindowInteractor( )->Render( ); 
}




int chrLandmarkSelector::IsViewValid( pqView* view )
{
   pqRenderView* renderView = qobject_cast<pqRenderView*>(view);
   if( renderView )
      return( 1 );
   else
      return( 0 );
}


