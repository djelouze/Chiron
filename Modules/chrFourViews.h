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
 
//! \class chrFourViews
//! \brief Create four views, 3 being 2D slicer and 1 being 3D view
//!
//! When activated, every existing views are removed. Then this module creates
//! 3 views and forces the representation of a volume to slice if any is 
//! selected. The camera is also set to parallel projection. 
//! A 4th 3D view is created.
//!
//! \author Jerome Velut
//! \date 12 dec 2009

#ifndef __CHRFOURVIEWS_H__
#define __CHRFOURVIEWS_H__

// Chiron includes
#include "chrApplicationModule.h"
#include "chrContextMenuModifier.h"
#include "chrSliceVolume.h"
#include "chrImageInfoOverlay.h"
#include "chrScaleInfoOverlay.h"
#include "chrClickAndSlice.h"
#include "chrLandmarkSelector.h"

// ParaView includes
#include "pqServer.h"
#include "pqObjectBuilder.h"
#include "pqServerManagerModel.h"
#include "pqRenderView.h"
#include "vtkSMRenderViewProxy.h"


class chrFourViews : public chrApplicationModule
{
public:
   //! Constructor:
   chrFourViews( );

   //! Destructor:
   virtual ~chrFourViews( );

   void Activate( );
   void Deactivate( );
   
protected:
   void activateViewModules( pqView* );

private:
      std::vector<chrViewModule*> viewModuleCollection;
};

#endif //__CHRFOURVIEWS_H__

