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

