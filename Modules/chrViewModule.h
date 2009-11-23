#ifndef __CHRVIEWMODULE_H__
#define __CHRVIEWMODULE_H__

// ParaView includes
#include "pqView.h"

// VTK includes
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkRenderWindowInteractor.h"

class chrViewModule
{
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

#endif //__CHRVIEWMODULE_H__

