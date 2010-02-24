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
      this->GetRenderWindowInteractor( )
          ->AddObserver( vtkCommand::MouseMoveEvent, this->Callback, 1.0 );
   }
   else
      cout << "View not initialized" << endl;
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
