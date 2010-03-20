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
 
//! \class chrLandmarkSelector
//! \brief Add PointSource to the pipeline centered on user mouse click.
//!
//! When activated, the click event is caught and route to this class
//! that adds a PointSource to the pipeline and centers it at the event
//! position.
//! When 'a' is pressed, the created PointSources are appended through
//! a vtkChainSource. The chain source is added to the pipeline and the point
//! sources are suppressed [not implemented].
//!
//! \todo Set this module as an application module.
//! \todo Implement the 'a' key press action.
//!
//! \author Jerome Velut
//! \date 14 dec 2009

#ifndef __CHRLANDMARKSELECTOR_H__
#define __CHRLANDMARKSELECTOR_H__

// Chiron includes
#include "chrViewModule.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"
#include "vtkSMDoubleVectorProperty.h"
#include "vtkCellArray.h"
#include "vtkPointPicker.h"
#include "vtkPoints.h"
#include "vtkProperty.h"

// ParaView includes
#include "pqServerManagerModel.h"
#include "pqObjectBuilder.h"
#include "pqPipelineSource.h"
#include "pqServer.h"

// std includes
#include <vector>
using namespace vtkstd;

class chrLandmarkSelector : public chrViewModule
{
Q_OBJECT

public:
   chrLandmarkSelector( );
   virtual ~chrLandmarkSelector( );

   virtual void Activate( );
   virtual void Deactivate( );

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
   //! Insert a PointSource in the pipeline centered on the user click
   void InsertPoint( );

   void AppendPointSources( );

   vtkEventQtSlotConnect* EventConnect;
   vector<pqPipelineSource*> PointSourceProxies;
};

#endif //__CHRLANDMARKSELECTOR_H__

