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
 
//! \class chrClickAndSlice
//! \brief Build a Polyline while slicing a volume.
//!
//! When activated, the click event is caught and route to this class
//! that increments the slice of every existing slice representation.
//! The click event position is used to append a points to a vtkPoints
//! list. When 'r' is pressed, a vtkChainSource is added to the 
//! current server based on the vtkPoints. Points are resetted.
//!
//!
//! \author Jerome Velut
//! \date 14 dec 2009

#ifndef __CHRCLICKANDSLICE_H__
#define __CHRCLICKANDSLICE_H__

// Chiron includes
#include "chrViewModule.h"
#include "vtkChainSource.h"

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

   //! Create a vtkChainSource based on UserPoint
   //! and add it to the first server
   void BuildPolylineSource( );

   vtkEventQtSlotConnect* EventConnect;
   vtkPoints* UserPoints;
};

#endif //__CHRCLICKANDSLICE_H__

