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
 
#include "chrViewModule.h"

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
      double black[3]  = {0, 0, 0};
      qobject_cast<pqRenderView*>(view)->getRenderViewProxy( )
                                       ->SetBackgroundColorCM( black );
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

