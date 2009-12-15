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
 
#include "chrClickAndSlice.h"

// ParaView includes
#include "pqDataRepresentation.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMProxy.h"

chrClickAndSlice::chrClickAndSlice( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
   this->UserPoints = vtkPoints::New( );
}


chrClickAndSlice::~chrClickAndSlice( )
{
   this->EventConnect->Delete( );
   this->UserPoints->Delete( );
}

void chrClickAndSlice::ButtonActivate( )
{
   if( this->GetView( ) != 0 )
   {
      this->AddButton( SLOT( toggleMode() ),
                       QIcon(":/Cursors/slice-32x32.png"),
                       1,
                       "Click'n Slice"
                     );
   }
}

void chrClickAndSlice::Activate( )
{
   if( this->GetView() )
      this->toggleMode( );
}

void chrClickAndSlice::Deactivate( )
{
   if( this->GetView() )
      this->toggleMode( );
}

void chrClickAndSlice::toggleMode( )
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
   }
   else
   {
      this->EventConnect->Disconnect( ); 
      this->Activated = 0;
   }
}

void chrClickAndSlice::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
}

void chrClickAndSlice::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->InsertPoint( );
   this->ChangeSlice( 1 );
}

void chrClickAndSlice::keyPress(vtkObject * obj, unsigned long,
                              void * client_data, void *,
                              vtkCommand * command)
{
   command->AbortFlagOn();
   if( this->GetRenderWindowInteractor( )->GetKeyCode() == 'r' ) // Set the points list as a PolylineSource
   {
      this->BuildPolylineSource( );
   }
}


void chrClickAndSlice::BuildPolylineSource( )
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
                                                 "PolylineSource", 
                                                 serversList[0] );
         if( pipelineSource )
         {
            vtkPolylineSource* objLineSource = 0;
            objLineSource = static_cast<vtkPolylineSource*>(pipelineSource->getProxy()->GetClientSideObject());
            if( objLineSource )
            {
               objLineSource->SetPoints( this->UserPoints );
               objLineSource->Update( );
               
               pipelineSource->getProxy()->UpdateSelfAndAllInputs();
               viewManager->getActiveView()->getRepresentation(0)->renderView(true);

               this->UserPoints->Reset( );
            }
         }
      }  
}

void chrClickAndSlice::ChangeSlice( int inc )
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

void chrClickAndSlice::InsertPoint( )
{
   int* position = this->GetRenderWindowInteractor( )->GetEventPosition();
      
   vtkPicker* picker = vtkPicker::New( );
   picker->Pick( position[0], position[1], 0, this->GetRenderer() );
   vtkPoints* pickedPositions = picker->GetPickedPositions( );
   
   int i;
   for( i = 0; i < pickedPositions->GetNumberOfPoints( ) ; i++)
   {
      double point[3];
      pickedPositions->GetPoint( i, point );
      this->UserPoints->InsertNextPoint( point );
      
   } 
}




int chrClickAndSlice::IsViewValid( pqView* view )
{
   pqRenderView* renderView = qobject_cast<pqRenderView*>(view);
   if( renderView )
      return( 1 );
   else
      return( 0 );
}


