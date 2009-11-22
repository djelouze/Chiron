#ifndef __CHRCHIRONMODULE_H__
#define __CHRCHIRONMODULE_H__

#include "pqView.h"
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkRenderWindowInteractor.h"

class chrViewModule{
public:
chrViewModule( );
virtual ~chrViewModule( );

void SetView( pqView* );
pqView* GetView( );

virtual void Activate( ) = 0;
virtual void Deactivate( ) = 0;

protected:
virtual int IsViewValid( pqView* ) = 0;

QVTKWidget* GetQVTKWidget( );
vtkRenderWindow* GetRenderWindow( );
vtkRenderer* GetRenderer( );
vtkRenderWindowInteractor* GetRenderWindowInteractor( );

private:
pqView* View;

};

#endif //__CHRCHIRONMODULE_H__

