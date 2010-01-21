//    Copyright Jerome Velut 2010
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

//! \class vtkStretchedCurvedPlanarReformation
//! \brief Axial reslicing of a volume along a path
//!
//! Stretched Curved Planar Reformation (Stretched-CPR) builds a 2D image from
//! an input path and an input volume. Each point of the path is considered as
//! the center of a 2D vtkImageReslicer. Reslicers output are appended on the z
//! axis.
//! Thus the output of this filter is a volume which central XZ-slice 
//! corresponding to the Stretched-CPR.
//!
//! Input: vtkImageData (InputConnection) and vtkPolyData (PathConnection) 
//! one polyline representing the path. Typically, the output of vtkSpline can
//! be used as path input.
//!
//! \todo Output extent is freezed on X extent = 511. Make it dependent on 
//! reslice direction and input volume.
//! \todo Because of reslice origin, CPR is only possible with slicing on x.
//! Make it more generic.
//! 
//! \see Kanitsar et al. "CPR - Curved Planar Reformation", Proc. IEEE  Visualization, 2002, 37-44
//! \author Jerome Velut
//! \date 21 jan 2010

#ifndef __VTKSTRETCHEDCURVEDPLANARREFORMATION_H__
#define __VTKSTRETCHEDCURVEDPLANARREFORMATION_H__

#include"vtkPoints.h"
#include"vtkImageAlgorithm.h"
#include"vtkPolyData.h"
#include"vtkCellArray.h"
#include "vtkImageReslice.h"

#if defined(NO_DLL)  && defined (WIN32)
   #undef VTK_EXPORT
   #define VTK_EXPORT
#endif

class VTK_EXPORT vtkStretchedCurvedPlanarReformation : public vtkImageAlgorithm
{
public:
   vtkTypeRevisionMacro(vtkStretchedCurvedPlanarReformation,vtkImageAlgorithm);
   static vtkStretchedCurvedPlanarReformation* New();

  //! Specify the path represented by a vtkPolyData wich contains PolyLines
  void SetPathConnection(int id, vtkAlgorithmOutput* algOutput);
  void SetPathConnection(vtkAlgorithmOutput* algOutput)
    {
      this->SetPathConnection(0, algOutput);
    };
  vtkAlgorithmOutput* GetPathConnection( )
                                 {return( this->GetInputConnection( 1, 0 ) );};

   vtkSetVector3Macro( xAxis, double );
   vtkGetVector3Macro( xAxis, double );

   vtkSetVector3Macro( yAxis, double );
   vtkGetVector3Macro( yAxis, double );

   vtkSetMacro( OutputThickness, double );
   vtkGetMacro( OutputThickness, double );

   vtkSetMacro( XYSpacing, double );
   vtkGetMacro( XYSpacing, double );

   vtkSetMacro( ZSpacing, double );
   vtkGetMacro( ZSpacing, double );

   vtkSetMacro( AutoZSpacing, int );
   vtkGetMacro( AutoZSpacing, int );
   vtkBooleanMacro( AutoZSpacing, int );



protected:
   vtkStretchedCurvedPlanarReformation();
   ~vtkStretchedCurvedPlanarReformation();

   virtual int RequestData(vtkInformation *, vtkInformationVector **, 
	                                         vtkInformationVector *);
   virtual int FillInputPortInformation(int port, vtkInformation *info);
   virtual int RequestInformation(vtkInformation*, vtkInformationVector**, 
	                                                vtkInformationVector*);
    virtual int RequestUpdateExtent(vtkInformation*, vtkInformationVector**, 
	                                                vtkInformationVector*);
   virtual int FillOutputPortInformation( vtkInformation*,
                                          vtkInformationVector**,
                                          vtkInformationVector*);

private:
   vtkStretchedCurvedPlanarReformation(const vtkStretchedCurvedPlanarReformation&);  // Not implemented.
   void operator=(const vtkStretchedCurvedPlanarReformation&);  // Not implemented.

   vtkImageReslice** reslicers; //!< Reslicers array

   double xAxis[3]; //!< output xAxis in volume coord. system
   double yAxis[3]; //!< output yAxis in volume coord. system (ie output thickness)

   double OutputThickness; //!< Number of pixels above and under the centre points
   double XYSpacing; //!< Pixel size
   double ZSpacing;  //!< Distance between slices
   int AutoZSpacing; //!< Specify if ZSpacing is computed from input sampling
};

#endif //__VTKSTRETCHEDCURVEDPLANARREFORMATION_H__
