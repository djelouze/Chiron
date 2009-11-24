#include "chrEventCatcher.h"

chrEventCatcher::chrEventCatcher( )
{
   this->Callback = vtkCallbackCommand::New( );
   this->Callback->SetCallback( chrEventCatcher::CatchEventCallback );
}


chrEventCatcher::~chrEventCatcher( )
{

}

void chrEventCatcher::Activate( )
{
   if( this->GetView( ) != 0 )
   {
      this->GetRenderWindowInteractor( )
          ->AddObserver( vtkCommand::MouseMoveEvent, this->Callback, 1.0 );
   }
   else
      cout << "View not initialized" << endl;
}

void chrEventCatcher::Deactivate( )
{
   if( this->GetView( ) != 0 )
   {
      this->GetRenderWindowInteractor( )
          ->RemoveObserver( vtkCommand::MouseMoveEvent );
   }
}

int chrEventCatcher::IsViewValid( pqView* view )
{
   return( 1 );
}

void chrEventCatcher::CatchEventCallback( vtkObject* obj, unsigned long eid, void* clientdata, void *calldata)
{
//   cout << "MouseMove" << endl;
}

