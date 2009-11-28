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

