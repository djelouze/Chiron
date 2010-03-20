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

