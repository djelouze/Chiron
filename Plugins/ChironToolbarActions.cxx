#include "ChironToolbarActions.h"

#include "chrEventCatcher.h"
#include "chrImageInfoOverlay.h"
#include "chrScaleInfoOverlay.h"

#include <QApplication>
#include <QStyle>
#include <QWheelEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QSlider>
#include <QObject>
#include <iostream>
#include "QVTKWidget.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"

#include "pqApplicationCore.h"
#include "pqMainWindowCore.h"
#include "pqObjectBuilder.h"
#include "pqServer.h"
#include "pqView.h"
#include "pqRenderView.h"

#include "pqActiveView.h"
#include "pqPipelineSource.h"
#include "pqDisplayPolicy.h"
#include "pqOutputPort.h"
#include "pqServerManagerModel.h"
#include "pqServerManagerSelectionModel.h"
#include "pqUndoStack.h"
#include "vtkSMProxy.h"
#include "vtkSMViewProxy.h"
#include "vtkSMOutputPort.h"
#include "vtkSMRenderViewProxy.h"
#include "vtkSMDimensionsDomain.h"
#include "vtkCamera.h"
#include "vtkSMDoubleVectorProperty.h"
#include "vtkSMIntVectorProperty.h"
#include "pqViewManager.h"
#include "pqPropertyManager.h"
#include "pqMultiViewFrame.h"
#include "pqDataRepresentation.h"
#include "pqServerResource.h"

#include "vtkEventQtSlotConnect.h"
//-----------------------------------------------------------------------------
ChironToolbarActions::ChironToolbarActions(QObject* p) : QActionGroup(p)
{
   // First Chiron toolbar button is checkable, but not exclusive
   this->setExclusive( false );

   // Adding buttons (ie actions) to the plugin's toolbar
   QAction* a;
   // Define a new action : Icon, tool tip and parent
   a = new QAction( QIcon(":/ToolbarIcons/chiron-256x256.png"), 
                    "Enable Chiron", 
                    this );
   a->setCheckable( true );
   
   // setData give the possibility to determine which button has been pressed
   a->setData("EnableChiron");

   // Add this action to the action group, ie the toolbar
   this->addAction(a);

   // New actions will be added here (property panels,...)
   // BEGIN NEW ACTIONS
 
   // END NEW ACTIONS   

   // Connect the signal triggered by the toolbar 
   // to the slot (ie function) onAction. 'triggered' 
   // is a signal sent when one of the toolbar button is pressed
   QObject::connect(this, SIGNAL(triggered(QAction*)), 
                    this, SLOT(onAction(QAction*)));
}

ChironToolbarActions::~ChironToolbarActions()
{
   while( !this->viewModuleList.empty( ) )
      this->viewModuleList.pop_back( );
}

//-----------------------------------------------------------------------------
void ChironToolbarActions::onAction(QAction* a)
{
   // Depending on which toolbar button has been clicked,
   // different actions are performed
   pqApplicationCore* core = pqApplicationCore::instance();
   pqObjectBuilder* builder = core->getObjectBuilder();
   pqServerManagerModel* sm = core->getServerManagerModel();
   pqServerManagerSelectionModel* smSel = core->getSelectionModel( );

   // item represents the current selected proxy in the pipeline browser
   pqServerManagerModelItem* item = smSel->currentItem();

   QString actionStr = a->data().toString();

   // Main activation button
   //   - activate/deactivate existing modules
   //   - connect to the viewCreated signal in order to 
   //     perform asynchronous activations
   if( actionStr == QString( "EnableChiron") )
   {
      // When Chiron is enabled, view creations are detected and connected
      // to each module
      this->connectToViewCreation( a->isChecked( ));
      if( a->isChecked( ) )
      {
         //! \todo loop over viewModuleList to activate them
      }
      else
      {
         //! \todo loop over viewModuleList to deactivate them
      }
   }
}

void ChironToolbarActions::connectToViewCreation( bool connect )
{
   pqApplicationCore* core = pqApplicationCore::instance();
   pqObjectBuilder* builder = core->getObjectBuilder();

   if( connect )
   {
      QObject::connect(builder, 
                       SIGNAL(viewCreated(pqView*)),
                       this,
                       SLOT(connectToChironModules(pqView*)));
   }
   else
   {
      QObject::disconnect(builder, 
                          SIGNAL(viewCreated(pqView*)), 
                          this,
                          SLOT(connectToChironModules(pqView*)));

   }
}


void ChironToolbarActions::connectToChironModules( pqView* view )
{
   chrEventCatcher* moduleEvent = new chrEventCatcher( );
   moduleEvent->SetView( view );
   moduleEvent->Activate( );

   chrImageInfoOverlay* moduleOverlay = new chrImageInfoOverlay( );
   moduleOverlay->SetView( view );
   moduleOverlay->Activate( );
   this->viewModuleList.push_back( moduleOverlay );
 
   chrScaleInfoOverlay* moduleScaleOverlay = new chrScaleInfoOverlay();
   moduleScaleOverlay->SetView( view );
   moduleScaleOverlay->Activate( );
}



