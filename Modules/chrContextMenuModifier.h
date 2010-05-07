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
 
//! \class chrContextMenuModifier
//! \brief Abstract class implementing a ParaView pqView-connected module.
//!
//! A chrContextMenuModifier is linked to a pqView in order to perform action 
//! independently on each view. Different accessors to the underlying VTK
//! visualisation pipeline are given (renderer, render window and interactor).
//! A child class has to implement the activation/deactivation processus and
//! a validator of the attached view type.
//!
//! \author Jerome Velut
//! \date 10 mar 2010

#ifndef __CHRCONTEXTMENUMODIFIER_H__
#define __CHRCONTEXTMENUMODIFIER_H__

// Chiron includes
#include "chrViewModule.h"

// ParaView includes
#include "pqRenderViewBase.h"
#include "pqApplicationCore.h"
#include "pqViewManager.h"
#include "pqMultiViewFrame.h"
#include "vtkSMRenderViewProxy.h"

// VTK includes
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkRenderWindowInteractor.h"

// QT include
#include <QIcon>
#include <QObject>

class chrContextMenuModifier : public chrViewModule
{

Q_OBJECT

public:
   //! Constructor.
   //! this->View is initialized to null pointer
   chrContextMenuModifier( );
   //! Destructor
   virtual ~chrContextMenuModifier( );

   virtual void Activate( ){this->Activated=1;};
   virtual void Deactivate( ){this->Activated=0;};
   virtual int IsViewValid( pqView* );
   
   //!
   void AddContextMenuItemToView( chrModule*, const char*, const char* slot=0x0 );

protected:

private:
   
};

#endif //__CHRCONTEXTMENUMODIFIER_H__

