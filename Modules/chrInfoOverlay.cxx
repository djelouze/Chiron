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
 
#include "chrInfoOverlay.h"


chrInfoOverlay::chrInfoOverlay( )
{
   this->InfoCollection = vtkPropCollection::New( );
}


chrInfoOverlay::~chrInfoOverlay( )
{
   this->InfoCollection->Delete( );
}

vtkTextActor* chrInfoOverlay::AddTextInfo( const char* defaultInfo )
{
   // Instanciate a new text actor that will be added to the renderer
   vtkTextActor* info = vtkTextActor::New( );
   info->SetInput( defaultInfo );

   this->AddProp( info );
   return( info );
}

void chrInfoOverlay::AddProp( vtkProp* prop )
{
   // Append to the info list
   this->InfoCollection->AddItem( prop );
}


void chrInfoOverlay::Layout( )
{
   // Init info list traversing
   this->InfoCollection->InitTraversal( );
   vtkProp* info;
   int infoId = 0;
   while( (info = this->InfoCollection->GetNextProp( ) ) != 0x0 )
   {
       // Default layout: - constant x (10 in display coordinate)
       //                 - y depends on info index
       vtkActor2D* text = vtkActor2D::SafeDownCast( info );
       if( text )
       {
          text->SetDisplayPosition( 10, infoId*15 + 10 );
          infoId ++;
       }
   }
}


void chrInfoOverlay::Activate( )
{
   if( this->GetView( ) != 0 && !this->Activated )
   {
 
      this->InfoCollection->InitTraversal( );
      vtkProp* info;
      vtkRenderer* renderer = this->GetRenderer( );
      while(   (info = this->InfoCollection->GetNextProp( ) ) != 0x0 
            && renderer != 0x0 )
         renderer->AddActor( info );
      
      this->Layout( );
      this->Activated = 1;
      this->GetRenderWindowInteractor( )->Render( );
   }
   else
   {
      // cout << "View not initialized" << endl;
      this->Activated = 0;
   }
}

void chrInfoOverlay::Deactivate( )
{
   if( this->GetView( ) != 0 && this->Activated )
   {
      vtkRenderer* renderer = this->GetRenderer( );
 
      this->InfoCollection->InitTraversal( );
      vtkProp* info;
      while( (info = this->InfoCollection->GetNextProp( ) ) != 0x0 )
         renderer->RemoveActor( info );

      this->Activated = 0;
   }
   //else
      // cout << "View not initialized" << endl;


}

int chrInfoOverlay::IsViewValid( pqView* view )
{
   // For now, the overlay is only possible for 3D render view)
   pqRenderView* renderView = qobject_cast<pqRenderView*>(view);
   
   if( renderView )
      return( 1 );
   else
      return( 0 );
}


