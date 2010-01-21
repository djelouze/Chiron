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

//! \class vtkFrenetSerretFrame
//! \brief Compute tangent and normal vectors to a polyline
//!
//! Given a polyline as input, this filter computes the Frenet-Serret frame
//! at each point. The output contains the tangent and normal vectors to the
//! curve. These vectors are appended, so that input array are not overwrited
//! \see vtkImagePathReslice for a use-case.
//!
//! \todo Comment this class. (cxx)
//! \todo [ENH] compute the whole chart (B=N^T) and put it in the 
//! PointData as a tensor.
//!
//! \author Jerome Velut
//! \date 21 jan 2010

#ifndef __VTKFRENETSERRETFRAME_H__
#define __VTKFRENETSERRETFRAME_H__

#include"vtkPoints.h"
#include"vtkPolyDataAlgorithm.h"
#include"vtkPolyData.h"
#include"vtkCellArray.h"

#if defined(NO_DLL)  && defined (WIN32)
   #undef VTK_EXPORT
   #define VTK_EXPORT
#endif

class VTK_EXPORT vtkFrenetSerretFrame : public vtkPolyDataAlgorithm
{
public:
   vtkTypeRevisionMacro(vtkFrenetSerretFrame,vtkPolyDataAlgorithm);
   static vtkFrenetSerretFrame* New();

   //! Set ConsistentNormals to 1 if you want your frames to be 'smooth'.
   //! Note that in this case, the normal to the curve will not represent the 
   //! acceleration, ie this is no more Frenet-Serret chart.
   vtkBooleanMacro( ConsistentNormals, int );
   vtkSetMacro( ConsistentNormals, int );
   vtkGetMacro( ConsistentNormals, int );

   //! Define the inclination of the consistent normals. Radian value.
   vtkSetMacro( ViewUp, double );
   vtkGetMacro( ViewUp, double );

   //! Rotate a vector around an axis
   //! \param [in] axis {Vector defining the axis to turn around.}
   //! \param [in] angle {Rotation angle in radian.}
   //! \param [out] vector {Vector to rotate. In place modification.}
   static void RotateVector( double* vector, const double* axis, double angle );


protected:
   vtkFrenetSerretFrame();
   ~vtkFrenetSerretFrame();

   virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
   virtual int FillInputPortInformation(int port, vtkInformation *info);

   //! Computes the derivative between 2 points (Next - Last).
   //! \param [in] pointIdNext {give first point Id}
   //! \param [in] pointIdLast {give second point Id}
   //! \param [out] tangent {fill a 3-array with the derivative value}
   //! \note If Next is [i+1], Last is [i-1], your are computing the 
   //! centered tangent at [i].
   void ComputeTangentVectors( vtkIdType pointIdNext,  
                               vtkIdType pointIdLast, 
                               double* tangent );

   //! Computes the second derivative between 2 points (Next - Last).
   //! \param [in] nextTg {give a first derivative}
   //! \param [in] lastTg {give a first derivative}
   //! \param [out] normal {fill a 3-array with the second derivative value}
   void ComputeNormalVectors( double *tgNext, 
                              double *tgLast, 
                              double* normal );

   //! ConsistentNormal depends on the local tangent and the last computed
   //! normal. This is a projection of lastNormal on the plan defined 
   //! by tangent.
   //! \param [in] tangent {give the tangent}
   //! \param [in] lastNormal {give the reference normal}
   //! \param [out] normal {fill a 3-array with the normal vector}
   void ComputeConsistentNormalVectors( double *tangent, 
                              double *lastNormal, 
                              double* normal );
private:
   vtkFrenetSerretFrame(const vtkFrenetSerretFrame&);  // Not implemented.
   void operator=(const vtkFrenetSerretFrame&);  // Not implemented.

   int ConsistentNormals; //!< Boolean. If 1, successive normals are computed
                          //!< in smooth manner. 
                          //!< \see ComputeConsistentNormalVectors
   double ViewUp; //!< Define the inclination of the normal vectors in case of
                  //!< ConsistentNormals is On
};

#endif //__VTKFRENETSERRETFRAME_H__
