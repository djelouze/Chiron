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

