//    Copyright Jerome Velut 2009
//
//    This file is part of Chiron.
//
//    Chiron is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Chiron is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You have received a copy of the GNU General Public License
//    along with Chiron in the file COPYING.  
//    If not, see <http://www.gnu.org/licenses/>.
 
//! \class chrChangeActiveView
//! \brief Simply adds several view modules to the active view
//!
//! When activated, the active view is linked to ScaleLegend, ImageInfo,
//! VolumeSlicer and WindowLevel view module.
//!
//! \author Jerome Velut
//! \date 12 dec 2009

#ifndef __CHRCHANGEACTIVEVIEW_H__
#define __CHRCHANGEACTIVEVIEW_H__

// Chiron includes
#include "chrApplicationModule.h"
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


class chrChangeActiveView : public chrApplicationModule
{
public:
   //! Constructor:
   chrChangeActiveView( );

   //! Destructor:
   virtual ~chrChangeActiveView( );

   void Activate( );
   void Deactivate( );
   
protected:
   void activateViewModules( pqView* );

private:
      std::vector<chrViewModule*> viewModuleCollection;
};

#endif //__CHRCHANGEACTIVEVIEW_H__

