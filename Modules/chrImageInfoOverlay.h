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

//! \class chrImageInfoOverlay
//! \brief Display image info on a renderer.
//!
//! This class overlays some image info, such as the extent/spacing, the VTK 
//! algorithm that produced this image but also the image intensity under the
//! mouse pointer.
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

#include "chrInfoOverlay.h"
#include "QVTKWidget.h"
#include "vtkAlgorithmOutput.h"
#include "vtkAlgorithm.h"
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

class chrImageInfoOverlay : public chrInfoOverlay{
public:
chrImageInfoOverlay( );
virtual ~chrImageInfoOverlay( );

//! Inherited from chrViewModule
virtual void Activate( );

protected:
//! Inherited from chrViewModule
virtual int IsViewValid( pqView* );

private:
vtkCallbackCommand* Callback;
static void OnMouseMove( vtkObject* obj, 
                         unsigned long eid, 
                         void* clientdata, 
                         void *calldata);

vtkTextActor* ImageName;
vtkTextActor* ImageExtent;
vtkTextActor* ImageSpacing;
vtkTextActor* ImageIntensity;
vtkTextActor* PointerCoordinates;

vtkCellPicker* CellPicker;
vtkPointPicker* PointPicker;

};

#endif //__CHRIMAGEINFOOVERLAY_H__

