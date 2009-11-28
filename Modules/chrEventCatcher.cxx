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

