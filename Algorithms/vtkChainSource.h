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
 
//! \class vtkChainSource
//! \brief VTK source based on a set of vtkPoints
//!
//! \todo Comments
//! 
//! \author Jerome Velut
//! \date 14 dec 2009

#ifndef __VTKPOLYLINESOURCE_H__
#define __VTKPOLYLINESOURCE_H__

#include "vtkPolyDataAlgorithm.h"
#include "vtkPoints.h"

class VTK_EXPORT vtkChainSource : public vtkPolyDataAlgorithm 
{
public:
  static vtkChainSource *New();
  vtkTypeRevisionMacro(vtkChainSource,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set position of first end point.
  vtkSetObjectMacro(Points,vtkPoints);
  vtkGetObjectMacro(Points,vtkPoints);

  vtkSetMacro( CellType, int );
  vtkGetMacro( CellType, int );

  void SetCellTypeToVertices( ){this->SetCellType(0);};
  void SetCellTypeToLines( ){this->SetCellType(1);};

protected:
  vtkChainSource( );
  ~vtkChainSource() {};

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  int RequestInformation(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  vtkPoints* Points;

private:
  vtkChainSource(const vtkChainSource&);  // Not implemented.
  void operator=(const vtkChainSource&);  // Not implemented.

  int CellType; //!< spcify if the output topology will be made of vertices or lines
};

#endif //__VTKPOLYLINESOURCE_H__
