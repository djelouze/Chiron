#include "chrScaleInfoOverlay.h"


chrScaleInfoOverlay::chrScaleInfoOverlay( )
{
   this->LegendScaleActor = vtkLegendScaleActor::New( );
   // Default configuration:
   this->LegendScaleActor->SetBottomAxisVisibility( 0 );
   this->LegendScaleActor->SetLeftAxisVisibility( 0 );
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
//! \todo Create a dialog box for vtkLegendScaleActor setting.
}
