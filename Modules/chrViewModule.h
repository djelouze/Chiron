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

// ParaView includes
#include "pqView.h"
#include "pqApplicationCore.h"
#include "pqViewManager.h"
#include "pqMultiViewFrame.h"

// VTK includes
#include "QVTKWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkRenderWindowInteractor.h"

// QT include
#include <QObject>
#include <QIcon>

class chrViewModule : public QObject
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

   //! Pure virtual function. Implement the processus of activation such as
   //! graphic object creation, Qt/VTK event dispatcher, etc.
   virtual void Activate( ) = 0;
   //! Pure virtual function. Child classes are responsible of freeing the
   //! view from added objects/actions.
   virtual void Deactivate( ) = 0;

protected:
   //! Check the view validity. Default is true for any pqView object.
   virtual int IsViewValid( pqView* ){return( 1 );};

   //! Add a button to the pqView toolbar. When the button is clicked,
   //! 'slot' is called. Typical use is to define a slot function in child
   //! classes and pass it to AddButton.
   //! \todo This is a PoC implementation. It would be nice to add any widgets
   //! to the view toolbar (slider, combobox,...)
   void AddButton( const char* slot, QIcon qicon );

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
   QHBoxLayout* bottomToolBar;
   
};

#endif //__CHRVIEWMODULE_H__

