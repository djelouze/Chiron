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
 
#include <chrSliceVolume.h>

// ParaView includes
#include <pqDataRepresentation.h>
#include <vtkSMIntVectorProperty.h>
#include <vtkSMProxy.h>
#include <vtkSMDimensionsDomain.h>

chrSliceVolume::chrSliceVolume( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
   this->Activated = 0;
   this->Dragging = 0;
   this->lastY = 0;
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


void chrSliceVolume::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   //command->AbortFlagOn();
   int lastx;
   this->GetRenderWindowInteractor( )->GetEventPosition( lastx, 
                                                         this->lastY );
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


