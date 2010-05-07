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
 
#include "chrImageInfoOverlay.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;


chrImageInfoOverlay::chrImageInfoOverlay( )
{
   this->Callback = vtkCallbackCommand::New( );
   this->Callback->SetCallback( chrImageInfoOverlay::OnMouseMove );
   this->Callback->SetClientData( this );

   this->PointerCoordinates = this->AddTextInfo("Coordinates");
   this->ImageIntensity = this->AddTextInfo("Intensity");
   this->ImageSpacing = this->AddTextInfo("Spacing");
   this->ImageExtent = this->AddTextInfo("Extent");
   this->ImageName = this->AddTextInfo("Name");

   this->CellPicker = vtkCellPicker::New( );
   this->PointPicker = vtkPointPicker::New( );
   
}

chrImageInfoOverlay::~chrImageInfoOverlay( )
{
   this->ImageName->Delete( );
   this->ImageExtent->Delete( );
   this->ImageSpacing->Delete( );
   this->PointerCoordinates->Delete( );
   this->ImageIntensity->Delete( );

   this->CellPicker->Delete( );
   this->PointPicker->Delete( );
}

void chrImageInfoOverlay::Activate( )
{
   // parent class is responsible of adding actor to the renderer.
   chrInfoOverlay::Activate( );

   if( this->Activated ) // Parent class has properly activated the module
   {
      // Watch for MouseMoveEvent
      this->MoveEventTag = this->GetRenderWindowInteractor( )
          ->AddObserver( vtkCommand::MouseMoveEvent, this->Callback, 1.0 );
   }
   else
      cout << "View not initialized" << endl;
}

void chrImageInfoOverlay::Deactivate( )
{

   if( this->Activated )
      this->GetRenderWindowInteractor( )
          ->RemoveObserver( this->MoveEventTag );

   chrInfoOverlay::Deactivate( );
}

int chrImageInfoOverlay::IsViewValid( pqView* view )
{
   return( chrInfoOverlay::IsViewValid( view ));
}

void chrImageInfoOverlay::OnMouseMove( vtkObject* obj, unsigned long eid, void* clientdata, void *calldata)
{
   int xyMouse[2];
   chrImageInfoOverlay* Self = static_cast<chrImageInfoOverlay*>(clientdata);

   vtkRenderWindowInteractor* iren = Self->GetRenderWindowInteractor( );
   iren->GetEventPosition( xyMouse[0], xyMouse[1] );

   Self->PointPicker->Pick( xyMouse[0], xyMouse[1], 0, 
                            iren->FindPokedRenderer(xyMouse[0], xyMouse[1] ));
   
   vtkIdType pointId = Self->PointPicker->GetPointId( );
   vtkDataSet* dataSet = Self->PointPicker->GetDataSet( );
   vtkImageData* imageData = vtkImageData::SafeDownCast( dataSet );
   if( imageData && pointId >= 0 )
   {
      ostringstream streamProducer;
      vtkAlgorithm* source = Self->UpstreamPipeline( imageData, 3 );
      vtkImageReader2* reader = vtkImageReader2::SafeDownCast( source );
      if( reader )
          if( reader->GetFileName( ) )
             streamProducer << reader->GetFileName( );
          else
             streamProducer << "Unknown name";
      else
         streamProducer << source->GetClassName( );
      Self->ImageName->SetInput( streamProducer.str().c_str() );

      ostringstream streamSpacing;
      ostringstream streamIntensity;
      double intensity = imageData->GetPointData( )
                                ->GetScalars( )
                                ->GetComponent( pointId, 0 );
      streamIntensity << intensity;
      Self->ImageIntensity->SetInput( streamIntensity.str().c_str() );

      double spacing[3];
      imageData->GetSpacing( spacing );
      streamSpacing << spacing[0] << " ; " 
              << spacing[1] << " ; "
              << spacing[2];
      Self->ImageSpacing->SetInput( streamSpacing.str().c_str() );

      ostringstream streamExtent;
      int extent[6];
      imageData->GetExtent( extent );
      streamExtent << extent[0] << " - " << extent[1] << " ; "
                    << extent[2]<< " - " << extent[3] << " ; "
                    << extent[4]<< " - " << extent[5];
      Self->ImageExtent->SetInput( streamExtent.str().c_str() );

      ostringstream streamPos;
      double position[3];
      Self->PointPicker->GetPickPosition( position );
      streamPos << position[0] << " ; " 
                   << position[1] << " ; " 
                   << position[2];
      Self->PointerCoordinates->SetInput( streamPos.str().c_str() );
   }

   iren->Render( );
}

vtkAlgorithm* chrImageInfoOverlay::UpstreamPipeline( vtkImageData* img,
                                                     int nbSteps )
{
   vtkAlgorithm* producer = img->GetProducerPort( )->GetProducer( );
   for( int i = 0; i < nbSteps; i++ )
      producer = producer->GetInputConnection( 0, 0 )->GetProducer( );

   return( producer );
}
