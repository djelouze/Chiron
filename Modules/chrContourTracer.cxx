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
 
#include "chrContourTracer.h"

// ParaView includes
#include "pqDataRepresentation.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMProxy.h"
#include "vtkSMPropertyIterator.h"
#include "vtkSMProxyProperty.h"

chrContourTracer::chrContourTracer( )
{
   this->EventConnect = vtkEventQtSlotConnect::New( );
   this->CurrentSplineSource = 0;
}


chrContourTracer::~chrContourTracer( )
{
   this->EventConnect->Delete( );
}


void chrContourTracer::Activate( )
{
   if( this->GetView() && !this->Activated )
   {
      this->toggleMode( );
   }
}

void chrContourTracer::Deactivate( )
{
   if( this->GetView() && this->Activated )
      this->toggleMode( );
}

void chrContourTracer::toggleMode( )
{
   if( !this->Activated )
   {
       this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::LeftButtonPressEvent,
                                  this,
                                  SLOT(leftButtonPress( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);

     this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::LeftButtonReleaseEvent,
                                  this,
                                  SLOT(leftButtonRelease( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);

       this->EventConnect->Connect(
                                  this->GetRenderWindowInteractor(),
                                  vtkCommand::KeyPressEvent,
                                  this,
                                  SLOT(keyPress( 
                                              vtkObject*, 
                                              unsigned long, 
                                              void*, 
                                              void*, 
                                              vtkCommand*)),
                                   this->GetView( ), 1.0);

      this->Activated = 1;
   }
   else
   {
      this->EventConnect->Disconnect( ); 
      this->Activated = 0;
   }
}

void chrContourTracer::leftButtonPress( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   if( this->GetRenderWindowInteractor( )->GetControlKey( ) )
      command->AbortFlagOn();
}

void chrContourTracer::leftButtonRelease( vtkObject* o, unsigned long eid,
                                void* clientdata, void* calldata,
                                vtkCommand* command)
{
   if( this->GetRenderWindowInteractor( )->GetControlKey( ) )
   {
      command->AbortFlagOn();
      this->InsertPoint( );
   }
}

void chrContourTracer::keyPress(vtkObject * obj, unsigned long,
                              void * client_data, void *,
                              vtkCommand * command)
{
   command->AbortFlagOn();
   // Validate the current spline
   if( this->GetRenderWindowInteractor( )->GetKeyCode() == 'v' )
   {
      this->CurrentSplineSource = 0;
      this->AddedPoints.erase(this->AddedPoints.begin(), this->AddedPoints.end());
      //! \todo Simulate a click on 'Apply' button here
   }
   // close/open the current spline
   if( this->GetRenderWindowInteractor( )->GetKeyCode() == 'c' )
   {
      vtkSMProxy* splineProxy = static_cast<vtkSMProxy*>(this->CurrentSplineSource->getProxy());
      vtkSMProxyProperty* paramFunctionProperty;
      paramFunctionProperty = static_cast<vtkSMProxyProperty*>(splineProxy->GetProperty( "ParametricFunction" ));
      vtkSMIntVectorProperty* closedProperty = 0;
      closedProperty = static_cast<vtkSMIntVectorProperty*>(paramFunctionProperty->GetProxy( 0 )->GetProperty( "Closed" ));
      int currentClosedState = closedProperty->GetElement( 0 );
      closedProperty->SetElement( 0, !currentClosedState );
   }
      
}

void chrContourTracer::InitializeSplineSource( )
{
   pqObjectBuilder* builder = pqApplicationCore::instance()->getObjectBuilder();
   pqServerManagerModel* smm = pqApplicationCore::instance()->getServerManagerModel();
   pqViewManager * viewManager = qobject_cast<pqViewManager*>
                 (pqApplicationCore::instance()->manager("MULTIVIEW_MANAGER"));

   QList<pqServer*> serversList = smm->findItems<pqServer*>( );

   // If at least one server exists, it adds a SplineSource to the first one
   // Should be changed to choose one server, shouldn't be?
   if( serversList.count() != 0 )
   {
      this->CurrentSplineSource = builder->createSource( "sources",
                                              "SplineSource",
                                              serversList[0] );
   }
}
 

void chrContourTracer::InsertPoint( )
{
   // Get the event position in window coordinate
   int* position = this->GetRenderWindowInteractor( )->GetEventPosition();

   // Retrieve the 3D coordinates intersecting objects      
   vtkPointPicker* picker = vtkPointPicker::New( );
   picker->Pick( position[0], position[1], 0, this->GetRenderer() );
   vtkPoints* pickedPositions = picker->GetPickedPositions( );

   // Get only one position (the last one for now)
   //! \todo Retain the closest to the camera
   int i;
   double* point = new double[3];
   for( i = 0; i < pickedPositions->GetNumberOfPoints( ) ; i++)
   {
      pickedPositions->GetPoint( i, point );
   }

   // the picked point is added to the current spline point list
   this->AddedPoints.push_back( point );

   if( !this->CurrentSplineSource ) // First click
   {
      this->InitializeSplineSource( );

   }


   // if the spline source has not been initialized, then do nothing
   if( this->CurrentSplineSource )
   {
      // The SplineSource proxy has a Points property attached to a 
      // ParametricFunction proxy. Retrieve it.
      vtkSMProxy* splineProxy = 0; 
      splineProxy = static_cast<vtkSMProxy*>(this->CurrentSplineSource->getProxy());
      if( !splineProxy ) // problem occurs with the spline proxy 
         return;
      vtkSMProxyProperty* paramFunctionProperty = 0;
      paramFunctionProperty = static_cast<vtkSMProxyProperty*>
                              (splineProxy->GetProperty("ParametricFunction"));
      if( !paramFunctionProperty ) // problem occurs with the parametric 
         return;                   // function property.
      vtkSMDoubleVectorProperty* pointsProperty = 0;
      pointsProperty = static_cast<vtkSMDoubleVectorProperty*>
                              (paramFunctionProperty
                               ->GetProxy( 0 )
                               ->GetProperty( "Points" ));
      if( !pointsProperty ) // problem occurs with the points property
         return;

      // Minimal number of points is 2 - according to the utilities.xml
      // At first user click, these 2 points are coincident at the user
      // click position
      int nbPoints = this->AddedPoints.size();
      int fakeNbPoints = nbPoints;
      if( nbPoints == 1 )
         fakeNbPoints = 2;

      // The set_number_command is used, meaning that the number of elements
      // will be the parameter of SetNumberOfPoints. All we have to do is
      // to give the property elements has a raw 1D pointer
      for( int idx = 0; idx < fakeNbPoints; idx++)
      {
         pointsProperty->SetElement( idx*3, 
                                     this->AddedPoints.at( idx%nbPoints )[0]);
         pointsProperty->SetElement( idx*3+1, 
                                     this->AddedPoints.at( idx%nbPoints )[1]);
         pointsProperty->SetElement( idx*3+2, 
                                     this->AddedPoints.at( idx%nbPoints )[2]);
      }
   }
}

int chrContourTracer::IsViewValid( pqView* view )
{
   pqRenderView* renderView = qobject_cast<pqRenderView*>(view);
   if( renderView )
      return( 1 );
   else
      return( 0 );
}


