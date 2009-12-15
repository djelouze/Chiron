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
 
//! \class chrClickAndSlice
//! \brief Build a Polyline while slicing a volume.
//!
//! When activated, the click event is caught and route to this class
//! that increments the slice of every existing slice representation.
//! The click event position is used to append a points to a vtkPoints
//! list. When 'r' is pressed, a vtkPolylineSource is added to the 
//! current server based on the vtkPoints. Points are resetted.
//!
//!
//! \author Jerome Velut
//! \date 14 dec 2009

#ifndef __CHRCLICKANDSLICE_H__
#define __CHRCLICKANDSLICE_H__

// Chiron includes
#include "chrViewModule.h"
#include "vtkPolylineSource.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"
#include "vtkPoints.h"
#include "vtkPicker.h"

// ParaView includes
#include "pqServerManagerModel.h"
#include "pqObjectBuilder.h"
#include "pqPipelineSource.h"
#include "pqServer.h"

class chrClickAndSlice : public chrViewModule
{
Q_OBJECT

public:
   chrClickAndSlice( );
   virtual ~chrClickAndSlice( );

   virtual void Activate( );
   virtual void Deactivate( );

   //! Add a button to the view menu bar that toggle activation
   void ButtonActivate( );

protected:
   virtual int IsViewValid( pqView* );

protected slots:
      void toggleMode( );

      void leftButtonPress(vtkObject * obj, unsigned long,
                   void * client_data, void *,
                   vtkCommand * command);


      void leftButtonRelease(vtkObject * obj, unsigned long,
                   void * client_data, void *,
                   vtkCommand * command);

      void keyPress(vtkObject * obj, unsigned long,
                      void * client_data, void *,
                      vtkCommand * command);

private:
   //! If a SliceRepresentation is visible in the view,
   //! then slice is added 'inc'.
   void ChangeSlice( int inc );

   //! Insert a point in UserPoint with position set
   //! to the last event that occurs in he interactor
   void InsertPoint( );

   //! Create a vtkPolylineSource based on UserPoint
   //! and add it to the first server
   void BuildPolylineSource( );

   vtkEventQtSlotConnect* EventConnect;
   vtkPoints* UserPoints;
};

#endif //__CHRCLICKANDSLICE_H__

