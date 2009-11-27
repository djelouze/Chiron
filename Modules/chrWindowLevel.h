#ifndef __CHRWINDOWLEVEL_H__
#define __CHRWINDOWLEVEL_H__

// Chiron includes
#include "chrViewModule.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"

class chrWindowLevel : public chrViewModule
{
Q_OBJECT

public:
   chrWindowLevel( );
   virtual ~chrWindowLevel( );

   virtual void Activate( );
   virtual void Deactivate( );

protected:
   virtual int IsViewValid( pqView* );

protected slots:
      void enterSliceMode( );
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
   int Activated;
   int Dragging;
   int lastY;
};

#endif //__CHRSLICEVOLUME

