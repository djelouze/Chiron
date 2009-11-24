#ifndef __CHREVENTCATCHER_H__
#define __CHREVENTCATCHER_H__

// Chiron includes
#include "chrViewModule.h"

// VTK includes
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCallbackCommand.h"

class chrEventCatcher : public chrViewModule
{
Q_OBJECT

public:
   chrEventCatcher( );
   virtual ~chrEventCatcher( );

   virtual void Activate( );
   virtual void Deactivate( );

protected:
   virtual int IsViewValid( pqView* );

protected slots:
   void NewButton( ){cout << "click" << endl;};

private:
   vtkCallbackCommand* Callback;

   static void CatchEventCallback( vtkObject* obj, 
                                   unsigned long eid, 
                                   void* clientdata, 
                                   void *calldata);

};

#endif //__CHREVENTCATCHER

