#include "chrWindowLevel.h"

// ParaView includes
#include "pqDataRepresentation.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMProxy.h"

chrWindowLevel::chrWindowLevel( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
   this->Activated = 0;
   this->Dragging = 0;
   this->lastY = 0;
}


chrWindowLevel::~chrWindowLevel( )
{

}

void chrWindowLevel::Activate( )
{
   if( this->GetView( ) != 0 )
   {
      this->AddButton( SLOT( enterSliceMode() ),
                       QIcon(":/Cursors/brightness-32x32.png"),
                       1,
                       "Window level"
                     );
   }
}
void chrWindowLevel::enterSliceMode( )
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



      this->GetQVTKWidget()
          ->setCursor( QCursor( QPixmap( ":/Cursors/brightness-32x32.png") ) );

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

void chrWindowLevel::Deactivate( )
{
}

void chrWindowLevel::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   int lastx;
   this->GetRenderWindowInteractor( )->GetEventPosition( lastx, 
                                                         this->lastY );
   this->Dragging = 1;
}

void chrWindowLevel::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->Dragging = 0;
}



void chrWindowLevel::mouseMove( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   int x, y;
   command->AbortFlagOn();
   if( this->Dragging )
   {
      this->GetRenderWindowInteractor( )->GetEventPosition( x, y );
      this->ChangeSlice( y - this->lastY );
   }
   this->lastY = y;
}

void chrWindowLevel::sliceDown( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->ChangeSlice( -1 );
}

void chrWindowLevel::sliceUp( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   command->AbortFlagOn();
   this->ChangeSlice( 1 );
}


void chrWindowLevel::ChangeSlice( int inc )
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

int chrWindowLevel::IsViewValid( pqView* view )
{
   return( 1 );
}


