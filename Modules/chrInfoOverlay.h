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
 
//! \class chrInfoOverlay
//! \brief Base class to add text actor as overlay on a view.
//!
//! chrInfoOverlay inherits from chrViewModule the capability of linking
//! to a ParaView view. 
//!
//! \author Jerome Velut
//! \date 13 dec 2009

#ifndef __CHRINFOOVERLAY_H__
#define __CHRINFOOVERLAY_H__

#include "chrViewModule.h"
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRendererCollection.h"
#include "vtkPropCollection.h"
#include "vtkCallbackCommand.h"
#include "vtkPicker.h"
#include "vtkTextActor.h"

class chrInfoOverlay : public chrViewModule{
public:
chrInfoOverlay( );
virtual ~chrInfoOverlay( );

//! Inherited from chrModule
virtual void Activate( );
virtual void Deactivate( );

protected:
//! Inherited from chrViewModule
virtual int IsViewValid( pqView* );

//! Add an information to overlay on the view. It adds a vtkTextActor to
//! the info collection and return it
vtkTextActor* AddTextInfo( const char* defaultText );

//! Add a 2D actor to the view
void AddProp( vtkProp* prop );

//! Initialize text actors' positions
virtual void Layout( );

private:

vtkPropCollection* InfoCollection;

};

#endif //__CHRINFOOVERLAY

