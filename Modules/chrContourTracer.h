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
 
//! \class chrContourTracer
//! \brief Add SplineSource to the pipeline. Add point by clicking on a render
//!  window.
//!
//! When activated, the click event is caught and route to this class
//! that adds a SplineSource to the pipeline. Each furthercoming click event
//! on the view append a point at the end of the spline.
//! 
//! When 'c' is pressed, the spline is validated. Continuying clicking will
//! add another spline.
//! 
//! \warning If chrSliceVolume is activated in the same time, the drag event
//! may be annoying when placing the spline points. Actual solution is to
//! activate first the ContourTracer module and then the SliceVolume module
//!
//! \todo Fix the dragging interference of SliceVolume
//! \todo Implement the 'c' key press action with closed/opened choice
//!
//! \author Jerome Velut
//! \date 20 mar 2010

#ifndef __CHRCONTOURTRACER_H__
#define __CHRCONTOURTRACER_H__

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

class chrContourTracer : public chrViewModule
{
Q_OBJECT

public:
   chrContourTracer( );
   virtual ~chrContourTracer( );

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
   //! Insert a point in the CurrentSplineSource
   void InsertPoint( );
   //! Add a SplineSource to the pipeline
   void InitializeSplineSource( );

   vtkEventQtSlotConnect* EventConnect;
   pqPipelineSource* CurrentSplineSource;
   vector<double*> AddedPoints; //! maintains a list of added points
};

#endif //__CHRCONTOURTRACER_H__

