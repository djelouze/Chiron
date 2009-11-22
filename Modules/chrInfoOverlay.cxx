#include "chrInfoOverlay.h"


chrInfoOverlay::chrInfoOverlay( )
{
   this->InfoCollection = vtkActor2DCollection::New( );
}


chrInfoOverlay::~chrInfoOverlay( )
{
   this->InfoCollection->Delete( );
}

vtkTextActor* chrInfoOverlay::AddInfo( const char* defaultInfo )
{
   // Instanciate a new text actor that will be added to the renderer
   vtkTextActor* info = vtkTextActor::New( );
   info->SetInput( defaultInfo );

   // Append to the info list
   this->InfoCollection->AddItem( info );
   
   return( info );
}


void chrInfoOverlay::Layout( )
{
   // Init info list traversing
   this->InfoCollection->InitTraversal( );
   vtkActor2D* info;
   int infoId = 0;
   while( (info = this->InfoCollection->GetNextActor2D( ) ) != 0x0 )
   {
       // Default layout: - constant x (10 in display coordinate)
       //                 - y depends on info index
       info->SetDisplayPosition( 10, infoId*15 + 10 );
       infoId ++;
   }
}


void chrInfoOverlay::Activate( )
{
   if( this->GetView( ) != 0 )
   {
      this->Layout( );
 
      this->InfoCollection->InitTraversal( );
      vtkActor2D* info;
      vtkRenderer* renderer = this->GetRenderer( );
      while(   (info = this->InfoCollection->GetNextActor2D( ) ) != 0x0 
            && renderer != 0x0 )
         renderer->AddActor( info );
   }
   else
      cout << "View not initialized" << endl;
}

void chrInfoOverlay::Deactivate( )
{
   if( this->GetView( ) != 0 )
   {

      vtkRendererCollection* renCollection = this->GetRenderWindow( )
                                                 ->GetRenderers( );
      //! \warning It may exists several renderers. Thus the first one is not
      //! necessary the good one.
      vtkRenderer* renderer = renCollection->GetFirstRenderer( );

      this->Layout( );
 
      this->InfoCollection->InitTraversal( );
      vtkActor2D* info;
      while( (info = this->InfoCollection->GetNextActor2D( ) ) != 0x0 )
         renderer->RemoveActor( info );
   }
   else
      cout << "View not initialized" << endl;


}

int chrInfoOverlay::IsViewValid( pqView* view )
{
   return( 1 );
}


