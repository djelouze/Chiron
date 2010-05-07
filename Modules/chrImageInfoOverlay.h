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

//! \class chrImageInfoOverlay
//! \brief Display image info on a renderer.
//!
//! This class overlays some image info, such as the extent/spacing, the VTK 
//! algorithm that produced this image but also the image intensity under the
//! mouse pointer. If the source "IsA" vtkImageReader2, the file name is printed
//! instead of the class name.
//!
//! \warning The paraview slicer induces a shadowed pipeline that doesn't
//! reflects the user pipeline (from pipeline browser). Effects are:
//!    - the image name seems exotic ("vtkPVUpdateSuppressor")
//!    - in 3D view, the slice representation is 0-dim in z.
//!    - in 2D view, the info are not updated when leaving the four first
//! slices.
//! \todo Investigate the picking in ParaView
//!
//! \author Jerome Velut
//! \date 29 nov 2009
 
#ifndef __CHRIMAGEINFOOVERLAY_H__
#define __CHRIMAGEINFOOVERLAY_H__

// Chiron includes
#include "chrInfoOverlay.h"

// ParaView includes"
#include "QVTKWidget.h"

// VTK includes
#include "vtkAlgorithmOutput.h"
#include "vtkAlgorithm.h"
#include "vtkImageReader2.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRendererCollection.h"
#include "vtkRenderer.h"
#include "vtkCallbackCommand.h"
#include "vtkCellPicker.h"
#include "vtkPointPicker.h"
#include "vtkTextActor.h"
#include "vtkImageData.h"
#include "vtkPointData.h"

class chrImageInfoOverlay : public chrInfoOverlay
{
public:
   //! Constructor
   chrImageInfoOverlay( );
   //! Destructor
   virtual ~chrImageInfoOverlay( );

   //! Inherited from chrViewModule
   virtual void Activate( );

   //! Inherited from chrViewModule
   virtual void Deactivate( );

protected:
   //! Inherited from chrViewModule
   virtual int IsViewValid( pqView* );

private:
   vtkCallbackCommand* Callback; //!< used to get mouse movement
   //! Callback function linked to a mouse move event
   static void OnMouseMove( vtkObject* obj, 
                         unsigned long eid, 
                         void* clientdata, 
                         void *calldata);
   long unsigned int MoveEventTag; //! set when the module is activated. Used
                                   //!  to remove the observer
   //! Find the nth upstream algorithm producing the given image data.
   vtkAlgorithm* UpstreamPipeline( vtkImageData* img, int n);

   vtkTextActor* ImageName; //!< Overlay info
   vtkTextActor* ImageExtent; //!< Overlay info
   vtkTextActor* ImageSpacing; //!< Overlay info
   vtkTextActor* ImageIntensity; //!< Overlay info
   vtkTextActor* PointerCoordinates; //!< Overlay info

   vtkCellPicker* CellPicker; //!< not used
   vtkPointPicker* PointPicker; //!< pick the image intensity
};

#endif //__CHRIMAGEINFOOVERLAY_H__

