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
 
#ifndef __CHRWINDOWLEVEL_H__
#define __CHRWINDOWLEVEL_H__

// Chiron includes
#include "chrViewModule.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"

class chrWindowLevel : public chrViewModule
{
Q_OBJECT

public:
   chrWindowLevel( );
   virtual ~chrWindowLevel( );

   virtual void Activate( );
   virtual void Deactivate( );

protected:
   virtual int IsViewValid( pqView* );

protected slots:
      void enterSliceMode( );
      void mouseMove(vtkObject * obj, unsigned long,
                 void * client_data, void *,
                 vtkCommand * command);
 
      void sliceDown(vtkObject * obj, unsigned long,
                 void * client_data, void *,
                 vtkCommand * command);
      void sliceUp(vtkObject * obj, unsigned long,
                     void * client_data, void *,
                     vtkCommand * command);
      void leftButtonPress(vtkObject * obj, unsigned long,
                   void * client_data, void *,
                   vtkCommand * command);
      void leftButtonRelease(vtkObject * obj, unsigned long,
                   void * client_data, void *,
                   vtkCommand * command);
//      void keyPress(vtkObject * obj, unsigned long,
//                      void * client_data, void *,
//                      vtkCommand * command);

private:
   //! If a SliceRepresentation is visible in the view,
   //! then slice is added 'inc'.
   void ChangeSlice( int inc );

   vtkEventQtSlotConnect* EventConnect;
   int Activated;
   int Dragging;
   int lastY;
};

#endif //__CHRSLICEVOLUME

