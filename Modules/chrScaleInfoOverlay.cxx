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

