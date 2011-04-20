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
 
#include "chrViewModule.h"

#include "vtkSMDoubleVectorProperty.h"
#include "pqTwoDRenderView.h"

chrViewModule::chrViewModule( )
{
   this->View = 0;
}


chrViewModule::~chrViewModule( )
{

}


void chrViewModule::SetView( pqView* view )
{
   if( this->IsViewValid( view ) && this->View != view )
   {
      this->View = view;
      double background[3]  = {0, 0, 0};
      vtkSMDoubleVectorProperty* bgColorProp;
      bgColorProp = static_cast<vtkSMDoubleVectorProperty*>(
                                   view->getViewProxy( )
                                   ->GetProperty( "Background" )
                       );
      bgColorProp->SetElements( background );
      view->getViewProxy()->UpdateProperty("Background");
      view->render();
   }
}

pqView* chrViewModule::GetView( )
{
   return( this->View );
}

QVTKWidget* chrViewModule::GetQVTKWidget( )
{
   if( this->GetView( ) )
      return( qobject_cast<QVTKWidget*>(this->GetView( )->getWidget( )));
   else
      return( 0 );
}

vtkRenderWindow* chrViewModule::GetRenderWindow( )
{
   QVTKWidget* qvtkWidget = this->GetQVTKWidget( );

   if( qvtkWidget )
      return( qvtkWidget->GetRenderWindow( ) );
   else
      return( 0 );
}

vtkRenderWindowInteractor* chrViewModule::GetRenderWindowInteractor( )
{
   vtkRenderWindow* renWin = this->GetRenderWindow( );

   if( renWin )
      return( renWin->GetInteractor( ) );
   else
      return( 0 );
}

vtkRenderer* chrViewModule::GetRenderer( )
{
   vtkRenderWindow* renWin = this->GetRenderWindow( );

   if( renWin )
   {
      vtkRendererCollection* renCollection = this->GetRenderWindow( )
                                                 ->GetRenderers( );
      //! \warning It may exists several renderers. Thus the first one is not
      //! necessary the good one.
      renCollection->InitTraversal( );
      vtkRenderer* renderer;
      while( (renderer = renCollection->GetNextItem( )) != 0 )
         if( renderer->GetLayer() == 0)
            return( renderer );
      return( renCollection->GetFirstRenderer( ) );
   }
   else
      return( 0 );
}

