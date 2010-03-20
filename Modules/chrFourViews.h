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

