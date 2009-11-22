#ifndef __CHRINFOOVERLAY_H__
#define __CHRINFOOVERLAY_H__

#include "chrViewModule.h"
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRendererCollection.h"
#include "vtkActor2DCollection.h"
#include "vtkCallbackCommand.h"
#include "vtkPicker.h"
#include "vtkTextActor.h"

class chrInfoOverlay : public chrViewModule{
public:
chrInfoOverlay( );
virtual ~chrInfoOverlay( );

//! Inherited from chrViewModule
virtual void Activate( );
virtual void Deactivate( );

protected:
//! Inherited from chrViewModule
virtual int IsViewValid( pqView* );
//! Add an information to overlay on the view. It adds a vtkTextActor to
//! the info collection and return it
vtkTextActor* AddInfo( const char* defaultText );

virtual void Layout( );

private:

vtkActor2DCollection* InfoCollection;

};

#endif //__CHRINFOOVERLAY

