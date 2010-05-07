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
 
//! \class chrScaleInfoOverlay
//! \brief Overlays rules on a VTK renderer
//! 
//! When activated, the concerned view renders a vtkLegendScaleActor.
//! A button is added to the view menu to toggle the actor visibility/
//!
//! \see vtkLegendScaleActor
//! \todo Add a property panel for user settings.
//!
//! \author Jerome Velut
//! \date 7 dec 2009

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

