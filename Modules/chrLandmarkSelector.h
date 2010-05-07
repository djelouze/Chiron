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

