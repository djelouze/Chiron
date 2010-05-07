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
 
//! \class chrWindowLevel
//! \brief Brings interactions for slicing a volume.
//!
//! When activated, the click event is caught and route to this class
//! that change the slice of every existing slice representation.
//! This is a little bit awkward and is about to change
//!
//! \todo Think about a "representaion picker" to slice only the picked volume.
//!
//! \author Jerome Velut
//! \date 3 may 2010

#ifndef __CHRWINDOWLEVEL_H__
#define __CHRWINDOWLEVEL_H__

// Chiron includes
#include "chrViewModule.h"

// ParaView includes
#include "pqScalarsToColors.h"

// VTK includes
#include "vtkEventQtSlotConnect.h"
#include "vtkImageData.h"
#include "vtkAlgorithm.h"
#include "vtkAlgorithmOutput.h"

class chrWindowLevel : public chrViewModule
{
Q_OBJECT

public:
   chrWindowLevel( );
   virtual ~chrWindowLevel( );

   virtual void Activate( );
   virtual void Deactivate( );

protected:
   virtual int IsViewValid( pqView* );

   vtkAlgorithm* UpstreamPipeline( vtkImageData* img, int nbStep );

protected slots:
      void toggleWindowLevelMode( );
      void mouseMove(vtkObject * obj, unsigned long,
                 void * client_data, void *,
                 vtkCommand * command);
 
      void leftButtonPress(vtkObject * obj, unsigned long,
                   void * client_data, void *,
                   vtkCommand * command);
      void leftButtonRelease(vtkObject * obj, unsigned long,
                   void * client_data, void *,
                   vtkCommand * command);
//      void keyPress(vtkObject * obj, unsigned long,
//                      void * client_data, void *,
//                      vtkCommand * command);

private:
   //! Change the window/level of the picked SliceRepresentation
   void ChangeWindowLevel( int winc, int linc );

   vtkEventQtSlotConnect* EventConnect;
   int Dragging;
   int lastY;
   int lastX;
   vtkAlgorithm* PickedAlgorithm;
};

#endif //__CHRWINDOWLEVEL_H__

