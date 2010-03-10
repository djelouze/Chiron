//    Copyright Jerome Velut 2009-2010
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
#include "chrModule.h"

// ParaView includes
#include "pqView.h"
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

class chrContextMenuModifier : QObject 
{

Q_OBJECT

public:
   //! Constructor.
   //! this->View is initialized to null pointer
   chrContextMenuModifier( );
   //! Destructor
   virtual ~chrContextMenuModifier( );

   //!
   void AddContextMenuItemToView( pqRenderViewBase*, const char*, chrModule* );

protected:

private:
   
};

#endif //__CHRCONTEXTMENUMODIFIER_H__

