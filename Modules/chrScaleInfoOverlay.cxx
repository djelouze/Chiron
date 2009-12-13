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

   this->AddProp( this->LegendScaleActor );
}

chrScaleInfoOverlay::~chrScaleInfoOverlay( )
{
   this->LegendScaleActor->Delete( );
}

void chrScaleInfoOverlay::Activate( )
{
   // parent class is responsible of adding actor to the renderer.
   chrInfoOverlay::Activate( );

   if( this->Activated )
   {
      this->AddButton( SLOT(setLegendProperty( )), 
                       QIcon(":/ToolbarIcons/scale-256x256.png" ),
                       1, // checkable
                       "Scale legend property")->setChecked( 1 );
   }
   else
      cout << "View not initialized" << endl;
}


int chrScaleInfoOverlay::IsViewValid( pqView* view )
{
   return( chrInfoOverlay::IsViewValid( view ) );
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

