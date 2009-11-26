#include "chrScaleInfoOverlay.h"

// VTK includes
#include "vtkAxisActor2D.h"

chrScaleInfoOverlay::chrScaleInfoOverlay( )
{
   this->LegendScaleActor = vtkLegendScaleActor::New( );
   // Default configuration:
   this->LegendScaleActor->SetBottomAxisVisibility( 0 );
   this->LegendScaleActor->SetLeftAxisVisibility( 0 );
   this->LegendScaleActor->SetLegendVisibility( 0 );
   this->LegendScaleActor->SetCornerOffsetFactor( 0 );
   this->LegendScaleActor->GetRightAxis( )->SetNumberOfLabels( 11 );
}

chrScaleInfoOverlay::~chrScaleInfoOverlay( )
{
   this->LegendScaleActor->Delete( );
}

void chrScaleInfoOverlay::Activate( )
{
   // parent class is responsible of adding actor to the renderer.
   chrInfoOverlay::Activate( );

   if( this->GetView( ) != 0 )
   {
      this->GetRenderer( )->AddActor( this->LegendScaleActor );
      this->AddButton( SLOT(setLegendProperty( )), 
                       QIcon(":/ToolbarIcons/scale-256x256.png" ));
   }
   else
      cout << "View not initialized" << endl;
}


int chrScaleInfoOverlay::IsViewValid( pqView* view )
{
   return( 1 );
}

void chrScaleInfoOverlay::setLegendProperty( )
{
   //! test: just toggle the scale legend visiblity
   int vis = this->LegendScaleActor->GetVisibility( );
   this->LegendScaleActor->SetVisibility( !vis );
   this->GetRenderWindow( )->Render( );
   //! \todo Create a dialog box for vtkLegendScaleActor setting.

//test mouse cursor change
//this->GetQVTKWidget()->setCursor( QCursor( QPixmap( ":/Cursors/slice-32x32.png") ) );
}

