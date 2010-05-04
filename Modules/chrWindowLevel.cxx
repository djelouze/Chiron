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
 
#include <chrWindowLevel.h>

//VTK includes
#include "vtkPicker.h"

// ParaView includes
#include <pqDataRepresentation.h>
#include <pqPipelineSource.h>
#include <vtkSMIntVectorProperty.h>
#include <vtkSMProxy.h>
#include <vtkSMDimensionsDomain.h>

chrWindowLevel::chrWindowLevel( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
   this->Activated = 0;
   this->Dragging = 0;
   this->lastY = 0;
   this->lastX = 0;
   this->PickedAlgorithm = 0;
}


chrWindowLevel::~chrWindowLevel( )
{

}


void chrWindowLevel::Activate( )
{
   if( this->GetView() )
      this->toggleWindowLevelMode( );
}

void chrWindowLevel::Deactivate( )
{
   if( this->GetView() )
      this->toggleWindowLevelMode( );
}

void chrWindowLevel::toggleWindowLevelMode( )
{
   if( !this->Activated )
   {
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


void chrWindowLevel::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   //command->AbortFlagOn();
   int lastx;
   vtkRenderWindowInteractor* renWinInt = this->GetRenderWindowInteractor( );
   renWinInt->GetEventPosition( this->lastX, this->lastY );
   vtkPicker* picker = vtkPicker::New( );
   picker->Pick( this->lastX, this->lastY, 0, this->GetRenderer() );
   vtkDataSet* dataSet = picker->GetDataSet();
   vtkImageData* imageData = vtkImageData::SafeDownCast( dataSet );
   if( imageData )
      this->PickedAlgorithm = this->UpstreamPipeline( imageData, 3 );

   this->Dragging = 1;
}

void chrWindowLevel::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   //command->AbortFlagOn();
   this->Dragging = 0;
}



void chrWindowLevel::mouseMove( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   int x = 0, y = 0;
   if( this->Dragging )
   {
      command->AbortFlagOn();
      this->GetRenderWindowInteractor( )->GetEventPosition( x, y );
      this->ChangeWindowLevel( y - this->lastY, x - this->lastX );
   }
   this->lastY = y;
   this->lastX = x;
}


void chrWindowLevel::ChangeWindowLevel( int winc, int linc )
{
   QList<pqRepresentation*> repList;
   repList = this->GetView( )->getRepresentations( );

   int multiplicator = 1;
   if( this->GetRenderWindowInteractor( )->GetShiftKey( ) )
      multiplicator = 10;

   int i = 0;
   for( i = 0; i < repList.count();i ++)
   {
      pqDataRepresentation* imageSlice = 0;
      imageSlice = qobject_cast<pqDataRepresentation*>(repList[i]);
      if( imageSlice )
      {
         
         if( imageSlice->isVisible( ) 
             && imageSlice->getInput()
                          ->getProxy()
                          ->GetClientSideObject() == this->PickedAlgorithm )
         {
            pqScalarsToColors* lut = 0;
            lut = imageSlice->getLookupTable();
            
            if( lut )
            {
               if( !lut->getScalarBar(qobject_cast<pqRenderViewBase*>(this->GetView() )))
               {
                  QPair<double, double> range = lut->getScalarRange( );
                  lut->setScalarRange(range.first+winc+linc,
                                      range.second-winc+linc );
                  imageSlice->renderView(true);
               }
            }
         }
      }
   }

}

int chrWindowLevel::IsViewValid( pqView* view )
{
   pqRenderViewBase* renderViewBase = qobject_cast<pqRenderViewBase*>(view);
   if( renderViewBase )
      return( 1 );
   else
      return( 0 );
}

vtkAlgorithm* chrWindowLevel::UpstreamPipeline( vtkImageData* img,
                                                     int nbSteps )
{
   vtkAlgorithm* producer = img->GetProducerPort( )->GetProducer( );
   for( int i = 0; i < nbSteps; i++ )
      producer = producer->GetInputConnection( 0, 0 )->GetProducer( );

   return( producer );
}

