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

