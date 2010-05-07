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
   pqRenderViewBase* renderView = qobject_cast<pqRenderViewBase*>(view);
   
   if( renderView )
      return( 1 );
   else
      return( 0 );
}


