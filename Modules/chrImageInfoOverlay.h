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
 
#ifndef __CHRIMAGEINFOOVERLAY_H__
#define __CHRIMAGEINFOOVERLAY_H__

#include "chrInfoOverlay.h"
#include "QVTKWidget.h"
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

