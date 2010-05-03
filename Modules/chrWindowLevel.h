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
 
//! \class chrWindowLevel
//! \brief Brings interactions for slicing a volume.
//!
//! When activated, the click event is caught and route to this class
//! that change the slice of every existing slice representation.
//! This is a little bit awkward and is about to change
//!
//! \todo Think about a "representaion picker" to slice only the picked volume.
//!
//! \author Jerome Velut
//! \date 3 may 2010

#ifndef __CHRWINDOWLEVEL_H__
#define __CHRWINDOWLEVEL_H__

// Chiron includes
#include "chrViewModule.h"

// ParaView includes
#include "pqScalarsToColors.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"
#include "vtkImageData.h"
#include "vtkAlgorithm.h"
#include "vtkAlgorithmOutput.h"

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

   vtkAlgorithm* UpstreamPipeline( vtkImageData* img, int nbStep );

protected slots:
      void toggleWindowLevelMode( );
      void mouseMove(vtkObject * obj, unsigned long,
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
   //! Change the window/level of the picked SliceRepresentation
   void ChangeWindowLevel( int winc, int linc );

   vtkEventQtSlotConnect* EventConnect;
   int Dragging;
   int lastY;
   int lastX;
   vtkAlgorithm* PickedAlgorithm;
};

#endif //__CHRWINDOWLEVEL_H__

