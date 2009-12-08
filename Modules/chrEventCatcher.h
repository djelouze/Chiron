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
 
//! \class chrEventCatcher
//! \brief Chiron view module that catches event. PoC class
//! 
//! This class will change a lot since this a Proof-of-Concept
//! container. Its role is to catch event, from ParaView or VTK
//! and to route them to Qt slot or VTK commands.
//! 
//! \author Jerome Velut
//! \date 7 dec 2009

#ifndef __CHREVENTCATCHER_H__
#define __CHREVENTCATCHER_H__

// Chiron includes
#include "chrViewModule.h"

// VTK includes
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCallbackCommand.h"

class chrEventCatcher : public chrViewModule
{
Q_OBJECT

public:
   chrEventCatcher( );
   virtual ~chrEventCatcher( );

   virtual void Activate( );
   virtual void Deactivate( );

protected:
   virtual int IsViewValid( pqView* );

private:
   vtkCallbackCommand* Callback;

   static void CatchEventCallback( vtkObject* obj, 
                                   unsigned long eid, 
                                   void* clientdata, 
                                   void *calldata);

};

#endif //__CHREVENTCATCHER

