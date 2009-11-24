#include "chrViewModule.h"

chrViewModule::chrViewModule( )
{
   this->View = 0;
   this->bottomToolBar = 0;
}


chrViewModule::~chrViewModule( )
{

}


void chrViewModule::SetView( pqView* view )
{
   if( this->IsViewValid( view ) )
      this->View = view;
}

pqView* chrViewModule::GetView( )
{
   return( this->View );
}

QVTKWidget* chrViewModule::GetQVTKWidget( )
{
   if( this->GetView( ) )
      return( qobject_cast<QVTKWidget*>(this->GetView( )->getWidget( )));
   else
      return( 0 );
}

vtkRenderWindow* chrViewModule::GetRenderWindow( )
{
   QVTKWidget* qvtkWidget = this->GetQVTKWidget( );

   if( qvtkWidget )
      return( qvtkWidget->GetRenderWindow( ) );
   else
      return( 0 );
}

vtkRenderWindowInteractor* chrViewModule::GetRenderWindowInteractor( )
{
   vtkRenderWindow* renWin = this->GetRenderWindow( );

   if( renWin )
      return( renWin->GetInteractor( ) );
   else
      return( 0 );
}

vtkRenderer* chrViewModule::GetRenderer( )
{
   vtkRenderWindow* renWin = this->GetRenderWindow( );

   if( renWin )
   {
      vtkRendererCollection* renCollection = this->GetRenderWindow( )
                                                 ->GetRenderers( );
      //! \warning It may exists several renderers. Thus the first one is not
      //! necessary the good one.
      vtkRenderer* renderer = renCollection->GetFirstRenderer( );
      return( renderer );
   }
   else
      return( 0 );
}

void chrViewModule::AddButton( const char* slot )
{
   pqApplicationCore* core = pqApplicationCore::instance();
   pqViewManager* viewManager = qobject_cast<pqViewManager*>
                                   (core->manager("MULTIVIEW_MANAGER"));
   pqMultiViewFrame* multiViewFrame = viewManager->getFrame( this->View );
 
   if( !this->bottomToolBar )
   {
      this->bottomToolBar = new QHBoxLayout( );
      this->bottomToolBar->setSpacing(0);
      this->bottomToolBar->setMargin(0);
      this->bottomToolBar->setObjectName(QString::fromUtf8("bottomToolBar"));
      qobject_cast<QVBoxLayout*>(multiViewFrame->layout( ))->addLayout( this->bottomToolBar);
      this->bottomToolBar->addStretch();

   }

   QAction* action = new QAction( QIcon(":/ToolbarIcons/chiron-256x256.png"),
                                  "Test", this );
   QToolButton* button = new QToolButton( multiViewFrame );
   button->setDefaultAction(action);
   button->setObjectName(action->objectName());
   this->bottomToolBar->insertWidget(0,button);
   QObject::connect( action, SIGNAL( triggered( bool )),
                     this, slot );
}
