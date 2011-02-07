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


