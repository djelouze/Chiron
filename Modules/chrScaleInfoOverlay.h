#ifndef __CHRSCALEINFOOVERLAY_H__
#define __CHRSCALEINFOOVERLAY_H__

// Chiron includes
#include "chrInfoOverlay.h"

// VTK includes
#include "vtkLegendScaleActor.h"

class chrScaleInfoOverlay : public chrInfoOverlay
{
Q_OBJECT

public:
   //! Constructor
   chrScaleInfoOverlay( );
   //! Destructor
   virtual ~chrScaleInfoOverlay( );

   //! Inherited from chrViewModule
   virtual void Activate( );

protected:
   //! Inherited from chrViewModule
   virtual int IsViewValid( pqView* );

protected slots:
   void setLegendProperty( );

private:
   vtkLegendScaleActor* LegendScaleActor;
};

#endif //__CHRSCALEINFOOVERLAY_H__

