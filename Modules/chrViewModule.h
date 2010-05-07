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
 
//! \class chrViewModule
//! \brief Abstract class implementing a ParaView pqView-connected module.
//!
//! A chrViewModule is linked to a pqView in order to perform action 
//! independently on each view. Different accessors to the underlying VTK
//! visualisation pipeline are given (renderer, render window and interactor).
//! A child class has to implement the activation/deactivation processus and
//! a validator of the attached view type.
//!
//! \author Jerome Velut
//! \date 23 nov 2009

#ifndef __CHRVIEWMODULE_H__
#define __CHRVIEWMODULE_H__

// Chiron includes
#include "chrModule.h"

// ParaView includes
#include "pqView.h"
#include "pqRenderView.h"
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

class chrViewModule : public chrModule
{

Q_OBJECT

public:
   //! Constructor.
   //! this->View is initialized to null pointer
   chrViewModule( );
   //! Destructor
   virtual ~chrViewModule( );

   //! Defines the view that will be linked to this module
   //! If view is not valid (\see IsViewValid ), this->View is not changed
   void SetView( pqView* );
   //! Return the pqView attached to this module
   pqView* GetView( );

   //! Check the view validity. Default is true for any pqView object.
   virtual int IsViewValid( pqView* ){return( 1 );};

protected:
   //! Get the QVTKWidget embedded in the pqView
   QVTKWidget* GetQVTKWidget( );
   //! Get the vtkRenderWindow embedded in the QVTKWidget
   vtkRenderWindow* GetRenderWindow( );
   //! Get the first renderer of the collection in vtkRenderWindow
   //! \todo Enhance the renderer traversal
   vtkRenderer* GetRenderer( );
   //! Get the vtkRenderWindowInteractor defined in the vtkRenderWindow
   vtkRenderWindowInteractor* GetRenderWindowInteractor( );

private:
   pqView* View;
   
};

#endif //__CHRVIEWMODULE_H__

