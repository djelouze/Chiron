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
 
#include <chrSliceVolume.h>

//VTK includes
#include "vtkPicker.h"

// ParaView includes
#include <pqServerManagerSelectionModel.h>
#include <pqPipelineRepresentation.h>
#include <pqPipelineSource.h>
#include <vtkSMIntVectorProperty.h>
#include <vtkSMProxy.h>
#include <vtkSMDimensionsDomain.h>

chrSliceVolume::chrSliceVolume( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
   this->Activated = 0;
   this->Dragging = 0;
   this->lastY = 0;
   this->PickedAlgorithm = 0;
}


chrSliceVolume::~chrSliceVolume( )
{

}


void chrSliceVolume::Activate( )
{
   if( this->GetView() )
      this->toggleSliceMode( );
}

void chrSliceVolume::Deactivate( )
{
   if( this->GetView() )
      this->toggleSliceMode( );
}

void chrSliceVolume::toggleSliceMode( )
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
                                  vtkCommand::MouseMoveEvent,
                                  this,
                                  SLOT(mouseMove( 
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



//      this->GetQVTKWidget()
//          ->setCursor( QCursor( QPixmap( ":/Cursors/slice-32x32.png") ) );
      this->ChangeSelectedProxyRepresentationToSlice( );
      this->Activated = 1;
   }
   else
   {
      this->EventConnect->Disconnect( ); 
      
      this->GetQVTKWidget()
          ->setCursor( QCursor( Qt::ArrowCursor ) );
      this->Activated = 0;
   }
}


void chrSliceVolume::ChangeSelectedProxyRepresentationToSlice( )
{
   pqServerManagerSelectionModel* selectionModel = this->Core
                                                       ->getSelectionModel();
   const pqServerManagerSelection* selectedItems;
   selectedItems = selectionModel->selectedItems ();

   // selectedItems is a list of pqServerManagerModelItem
   int i;
   for( int i = 0; i < selectedItems->size( );i++ )
   {
      pqServerManagerModelItem* item = selectedItems->at(i);
      pqPipelineSource* source = static_cast<pqPipelineSource*>(item);
      if( source )
      {
       //! \todo Implement the representation check, ie is slicing possible...
         pqOutputPort* outputPort = source->getOutputPort( 0 );
         if( outputPort )
         {
            if( !strcmp( outputPort->getDataClassName(), "vtkImageData" ))
            {
               pqPipelineRepresentation* rep = qobject_cast<pqPipelineRepresentation*>(outputPort->getRepresentation( 
                                                    this->GetView()));
               // 6 is ImageSliceRepresentation
               // 3 is outline
               if( rep->getRepresentationType() != 6 )
                  rep->setRepresentation( 6 );
               this->GetView()->render();
            }
         }
      }
   }
}

void chrSliceVolume::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   //command->AbortFlagOn();
   int lastx;
   vtkRenderWindowInteractor* renWinInt = this->GetRenderWindowInteractor( );
   renWinInt->GetEventPosition( lastx, this->lastY );
   vtkPicker* picker = vtkPicker::New( );
   picker->Pick( lastx, this->lastY, 0, this->GetRenderer() );
   vtkDataSet* dataSet = picker->GetDataSet();
   vtkImageData* imageData = vtkImageData::SafeDownCast( dataSet );
   if( imageData )
      this->PickedAlgorithm = this->UpstreamPipeline( imageData, 0 );

   this->Dragging = 1;
}

void chrSliceVolume::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   //command->AbortFlagOn();
   this->Dragging = 0;
}



void chrSliceVolume::mouseMove( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   int x = 0, y = 0;
   if( this->Dragging )
   {
      command->AbortFlagOn();
      this->GetRenderWindowInteractor( )->GetEventPosition( x, y );
      this->ChangeSlice( y - this->lastY );
   }
   this->lastY = y;
}

void chrSliceVolume::sliceDown( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->ChangeSlice( -1 );
}

void chrSliceVolume::sliceUp( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->ChangeSlice( 1 );
}


void chrSliceVolume::ChangeSlice( int inc )
{
   QList<pqRepresentation*> repList;
   repList = this->GetView( )->getRepresentations( );

   int multiplicator = 1;
   if( this->GetRenderWindowInteractor( )->GetShiftKey( ) )
      multiplicator = 10;

   for( int i = 0; i < repList.count();i ++)
   {
      pqDataRepresentation* imageSlice = 0;
      imageSlice = qobject_cast<pqDataRepresentation*>(repList[i]);
      if( imageSlice )
      {
         if( imageSlice->isVisible( )) 
             //&& imageSlice->getInput()->getProxy()->GetClientSideObject() 
             //   == this->PickedAlgorithm )
         {
            vtkSMIntVectorProperty* ivp = 0;
            ivp = vtkSMIntVectorProperty::SafeDownCast( imageSlice->getProxy()
                  ->GetProperty("Slice"));
            
            if( ivp )
            {

               vtkSMDimensionsDomain* domain = static_cast<vtkSMDimensionsDomain*>(ivp->GetDomain( "dims" ));
               int currentSlice = ivp->GetElement( 0 );
               int nextSlice = currentSlice + inc * multiplicator;
 
               // Clamp the slice value to the image extent
               int exists;
               int min = domain->GetMinimum( 0, exists );
               int max = domain->GetMaximum( 0, exists );
               if( nextSlice < min )
                  nextSlice = min;
               if( nextSlice > max )
                  nextSlice = max;
               
               ivp->SetElement(0, nextSlice );

               imageSlice->getProxy()->UpdateVTKObjects();
               imageSlice->renderView(true);
            }
         }
      }
      else
      {
//         cout << "No ImageSlice representations" << endl;
      }
   }

}

int chrSliceVolume::IsViewValid( pqView* view )
{
   pqRenderViewBase* renderViewBase = qobject_cast<pqRenderViewBase*>(view);
   if( renderViewBase )
      return( 1 );
   else
      return( 0 );
}

vtkAlgorithm* chrSliceVolume::UpstreamPipeline( vtkImageData* img,
                                                     int nbSteps )
{
   vtkAlgorithm* producer = img->GetProducerPort( )->GetProducer( );
   for( int i = 0; i < nbSteps; i++ )
      producer = producer->GetInputConnection( 0, 0 )->GetProducer( );

   return( producer );
}

