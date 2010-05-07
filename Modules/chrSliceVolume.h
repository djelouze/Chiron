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
#include "vtkImageData.h"
#include "vtkAlgorithm.h"
#include "vtkAlgorithmOutput.h"

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

   vtkAlgorithm* UpstreamPipeline( vtkImageData* img, int nbStep );

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
   vtkAlgorithm* PickedAlgorithm;
};

#endif //__CHRSLICEVOLUME

