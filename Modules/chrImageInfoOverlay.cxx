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

   this->ImageName = this->AddInfo("ImageName");
   this->ImageExtent = this->AddInfo("ImageExtent");
   this->ImageSpacing = this->AddInfo("ImageSpacing");
   this->PointerCoordinates = this->AddInfo("PointerCoordinates");
   this->ImageIntensity = this->AddInfo("ImageIntensity");

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

   if( this->GetView( ) != 0 )
   {
      this->GetRenderWindowInteractor( )
          ->AddObserver( vtkCommand::MouseMoveEvent, this->Callback, 1.0 );
   }
   else
      cout << "View not initialized" << endl;
}

int chrImageInfoOverlay::IsViewValid( pqView* view )
{
   return( 1 );
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
   if( imageData )
   {
      ostringstream streamIntensity;
      double intensity = imageData->GetPointData( )
                                ->GetScalars( )
                                ->GetComponent( pointId, 0 ); 
      streamIntensity << intensity;
      Self->ImageIntensity->SetInput( streamIntensity.str().c_str() );

      ostringstream streamSpacing;
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



   }

   iren->Render( );
}

