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

