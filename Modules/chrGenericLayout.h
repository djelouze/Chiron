// Copyright (c) 2010, Jérôme Velut
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER ``AS IS'' AND ANY EXPRESS 
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN 
// NO EVENT SHALL THE COPYRIGHT OWNER BE LIABLE FOR ANY DIRECT, INDIRECT, 
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
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
#include "chrImageInfoOverlay.h"
#include "chrScaleInfoOverlay.h"

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

   virtual void Activate( );
   virtual void Deactivate( );
   
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

      std::vector<chrViewModule*> viewModuleCollection;
};

#endif //__CHRGENERICLAYOUT

