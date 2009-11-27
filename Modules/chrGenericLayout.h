//! \class chrGenericLayout
//! \brief Creates 4 RenderViews in ParaView with different Chrion modules
//!
//! When activated, 4 RenderViews are built and linked to WindowLevel,
//! SliceVolume and LegendScale modules.
//!
//! \author Jerome Velut
//! \date 27 nov 2009

#ifndef __CHRGENERICLAYOUT_H__
#define __CHRGENERICLAYOUT_H__

// Chiron includes
#include "chrApplicationModule.h"
#include "chrSliceVolume.h"

// ParaView includes
#include "pqServer.h"
#include "pqObjectBuilder.h"
#include "pqServerManagerModel.h"
#include "pqRenderView.h"
#include "vtkSMRenderViewProxy.h"

// VTK includes
#include "vtkCamera.h"

class chrGenericLayout : public chrApplicationModule
{
Q_OBJECT

public:
   //! Constructor:
   chrGenericLayout( );

   //! Destructor:
   virtual ~chrGenericLayout( );

   void Activate( );

protected:
   void createViews( pqServer* );
   void resetViewDirection( );

protected slots:
   void activateViewModules( pqView* );

private:
      pqView* xyView;
      pqView* xzView;
      pqView* yzView;
      pqView* threeDView;

};

#endif //__CHRGENERICLAYOUT

