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

//! \class vtkStraightenedCurvedPlanarReformation
//! \brief Orthogonal reslicing of a volume along a path
//!
//! Straightened Curved Planar Reformation (Stretched-CPR) builds a 2D image
//! from an input path and an input volume. Each point of the path is
//! considered as the center of a 2D vtkImageReslicer. Reslicers axes are set
//! orthogonal to the path. Reslicers output are appended on the z axis. Thus
//! the output of this filter is a volume with central XZ- and YZ-slices
//! corresponding to the Straightened-CPR.
//!
//! Input: vtkImageData (InputConnection) and vtkPolyData (PathConnection)
//! one polyline representing the path. Typically, the output of vtkSpline can
//! be used as path input.
//!
//! \see Kanitsar et al. "CPR - Curved Planar Reformation", Proc. IEEE  Visualization, 2002, 37-44
//! \author Jerome Velut
//! \date 21 jan 2010

#ifndef __VTKSTRAIGHTENEDCURVEDPLANARREFORMATION_H__
#define __VTKSTRAIGHTENEDCURVEDPLANARREFORMATION_H__

#include"vtkPoints.h"
#include"vtkImageAlgorithm.h"
#include"vtkPolyData.h"
#include"vtkCellArray.h"
#include "vtkFrenetSerretFrame.h"
#include "vtkImageReslice.h"

#if defined(NO_DLL)  && defined (WIN32)
#undef VTK_EXPORT
#define VTK_EXPORT
#endif

class VTK_EXPORT vtkStraightenedCurvedPlanarReformation : public vtkImageAlgorithm
{
public:
    vtkTypeRevisionMacro(vtkStraightenedCurvedPlanarReformation,vtkImageAlgorithm);
    static vtkStraightenedCurvedPlanarReformation* New();

    //! Specify the path represented by a vtkPolyData wich contains PolyLines
    void SetPathConnection(int id, vtkAlgorithmOutput* algOutput);
    void SetPathConnection(vtkAlgorithmOutput* algOutput)
    {
        this->SetPathConnection(0, algOutput);
    };
    vtkAlgorithmOutput* GetPathConnection( )
    {
        return( this->GetInputConnection( 1, 0 ) );
    };

    vtkSetMacro( SliceSize, double );
    vtkGetMacro( SliceSize, double );

    vtkSetMacro( XYSpacing, double );
    vtkGetMacro( XYSpacing, double );

    vtkSetMacro( ZSpacing, double );
    vtkGetMacro( ZSpacing, double );

    vtkSetMacro( AutoZSpacing, int );
    vtkGetMacro( AutoZSpacing, int );
    vtkBooleanMacro( AutoZSpacing, int );

    vtkSetMacro( Incidence, double );
    vtkGetMacro( Incidence, double );


protected:
    vtkStraightenedCurvedPlanarReformation();
    ~vtkStraightenedCurvedPlanarReformation();

    virtual int RequestData(vtkInformation *, vtkInformationVector **,
                            vtkInformationVector *);
    virtual int RequestUpdateExtent(vtkInformation *, vtkInformationVector **,
                                    vtkInformationVector *);
    virtual int FillInputPortInformation(int port, vtkInformation *info);
    virtual int RequestInformation(vtkInformation*, vtkInformationVector**,
                                   vtkInformationVector*);
    virtual int FillOutputPortInformation( vtkInformation*,
                                           vtkInformationVector**,
                                           vtkInformationVector*);

private:
    vtkStraightenedCurvedPlanarReformation(const vtkStraightenedCurvedPlanarReformation&);  // Not implemented.
    void operator=(const vtkStraightenedCurvedPlanarReformation&);  // Not implemented.

    vtkFrenetSerretFrame* localFrenetFrames; //!< computes local tangent along path input
    vtkImageReslice** reslicers; //!< Reslicers array

    double SliceSize; //!< Number of pixels around the center points
    double XYSpacing; //!< Pixel size
    double ZSpacing;  //!< Distance between slices
    int AutoZSpacing; //!< Specify if ZSpacing is computed from input sampling
    double Incidence; //!< Rotation of the initial normal vector.

};

#endif //__VTKSTRAIGHTENEDCURVEDPLANARREFORMATION_H__
