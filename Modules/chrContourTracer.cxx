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
 
#include "chrContourTracer.h"

// ParaView includes
#include "pqDataRepresentation.h"
#include "vtkSMIntVectorProperty.h"
#include "vtkSMSourceProxy.h"
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
   //if( this->GetRenderWindowInteractor( )->GetControlKey( ) )
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
      if( this->CurrentSplineSource )
      {
         // Update the VTK side of the force
         this->CurrentSplineSource->getProxy()->UpdateSelfAndAllInputs( );
         // Set the proxy as visible through representation
         pqRepresentation* rep = 0;
         rep = static_cast<pqRepresentation*>(this->CurrentSplineSource->getRepresentation( this->GetView() ));
         // but if it doesn't exist (it is the case after fresh proxy creation), create a representation
         if( !rep )
         {
            pqObjectBuilder* builder = pqApplicationCore::instance()->getObjectBuilder();
            rep = builder->createDataRepresentation( this->CurrentSplineSource
                                                         ->getOutputPort( 0 ),
                                                     this->GetView( ));
         }
         // and set it as visible
         rep->setVisible(true);
         // Then update the pipeline information, render and set the spline as
         // unmodified (will switch off the "Apply" button).
         static_cast<vtkSMSourceProxy*>(this->CurrentSplineSource->getProxy())->UpdatePipelineInformation( );
         this->Core->render();
         this->CurrentSplineSource->setModifiedState( pqProxy::UNMODIFIED );
         vtkSMIntVectorProperty* pickable = 0;
         pickable = static_cast<vtkSMIntVectorProperty*>(rep->getProxy()->GetProperty( "Pickable" ));
         if( pickable )
         {
            pickable->SetElement( 0, 0 );
            rep->getProxy()->UpdateProperty( "Pickable" );
         }
      }

      // Now the current spline is an independent paraview object
      this->CurrentSplineSource = 0;

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
      this->AddedPoints.erase(this->AddedPoints.begin(), this->AddedPoints.end());
      QObject::connect( this->CurrentSplineSource, SIGNAL( destroyed(QObject*) ),
                        this, SLOT( destroyedSplineSource( QObject* ) ) );
      this->CurrentSplineSource->updatePipeline();
   }
}
 

int chrContourTracer::destroyedSplineSource( QObject* splineSource )
{
   this->CurrentSplineSource = 0;
}

void chrContourTracer::InsertPoint( )
{
   // First click
   if( !this->CurrentSplineSource ) // First click
   {
      this->InitializeSplineSource( );

   }

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
      //this->CurrentSplineSource->setModifiedState( pqProxy::MODIFIED );
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


