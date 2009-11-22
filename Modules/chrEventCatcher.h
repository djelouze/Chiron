#ifndef __CHREVENTCATCHER_H__
#define __CHREVENTCATCHER_H__

#include "chrViewModule.h"
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCallbackCommand.h"

class chrEventCatcher : public chrViewModule{
public:
chrEventCatcher( );
virtual ~chrEventCatcher( );

virtual void Activate( );
virtual void Deactivate( );

protected:
virtual int IsViewValid( pqView* );

private:
vtkCallbackCommand* Callback;

static void CatchEventCallback( vtkObject* obj, unsigned long eid, void* clientdata, void *calldata);

};

#endif //__CHREVENTCATCHER

