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
 
//! \class chrContourTracer
//! \brief Add SplineSource to the pipeline. Add point by clicking on a render
//!  window.
//!
//! When activated, the click event is caught and route to this class
//! that adds a SplineSource to the pipeline. Each furthercoming click event
//! on the view append a point at the end of the spline.
//! 
//! When 'v' is pressed, the spline is validated. Continuying clicking will
//! add another spline.
//! 
//! When 'c' is pressed, the closed state is toggled.
//!
//! \warning If chrSliceVolume is activated in the same time, the drag event
//! may be annoying when placing the spline points. Actual solution is to
//! activate first the ContourTracer module and then the SliceVolume module
//!
//! \todo Fix the dragging interference of SliceVolume
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
   //! Constructor. Allocate the EventConnect member and initialize the 
   //! CurrentSplineSource to 0
   chrContourTracer( );
   virtual ~chrContourTracer( );

   virtual void Activate( );
   virtual void Deactivate( );

   //! Valid view are pqRenderView (3D view)
   virtual int IsViewValid( pqView* );

protected slots:
      //! Toggle activated/deactivated state
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

      int destroyedSplineSource( QObject* );

private:
   //! Insert a point in the CurrentSplineSource
   void InsertPoint( );
   //! Add a SplineSource to the pipeline
   void InitializeSplineSource( );

   vtkEventQtSlotConnect* EventConnect; //!< Internal event connector
   pqPipelineSource* CurrentSplineSource; //!< SplineSource in use
   vector<double*> AddedPoints; //!< maintains a list of added points
};

#endif //__CHRCONTOURTRACER_H__

