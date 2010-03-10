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
 
//! \class chrSliceVolume
//! \brief Brings interactions for slicing a volume.
//!
//! When activated, the click event is caught and route to this class
//! that change the slice of every existing slice representation.
//! This is a little bit awkward and is about to change
//!
//! \todo Think about a "representaion picker" to slice only the picked volume.
//!
//! \author Jerome Velut
//! \date 7 dec 2009

#ifndef __CHRSLICEVOLUME_H__
#define __CHRSLICEVOLUME_H__

// Chiron includes
#include "chrViewModule.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"

class chrSliceVolume : public chrViewModule
{
Q_OBJECT

public:
   chrSliceVolume( );
   virtual ~chrSliceVolume( );

   virtual void Activate( );
   virtual void Deactivate( );

protected:
   virtual int IsViewValid( pqView* );

protected slots:
      void toggleSliceMode( );
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
   int Dragging;
   int lastY;
};

#endif //__CHRSLICEVOLUME

