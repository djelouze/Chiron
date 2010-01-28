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

#include "vtkChainSource.h"

#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"

vtkCxxRevisionMacro(vtkChainSource, "$Revision: 1.48 $");
vtkStandardNewMacro(vtkChainSource);

vtkChainSource::vtkChainSource()
{
  this->CellType = 0;
  this->Points = 0;
  this->SetNumberOfInputPorts(0);
}

int vtkChainSource::RequestInformation(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  // get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::MAXIMUM_NUMBER_OF_PIECES(),
               -1);
  return 1;
}

int vtkChainSource::RequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *outputVector)
{
  // get the info object
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  // get the ouptut
  vtkPolyData *output = vtkPolyData::SafeDownCast(
    outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkPoints *newPoints; 
  vtkCellArray *newLines;
  
  if (outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER()) > 0)
    {
    return 1;
    }

  newPoints = vtkPoints::New();
  newLines = vtkCellArray::New();
  newLines->InsertNextCell( this->Points?this->Points->GetNumberOfPoints():0 );

  if( this->Points )
     for( int id = 0; id < this->Points->GetNumberOfPoints( ); id ++ )//
     {
        vtkIdType newId = newPoints->InsertNextPoint(this->Points->GetPoint( id ));
        newLines->InsertCellPoint( newId );
    }
  
    output->SetPoints(newPoints);
  newPoints->Delete();

  if( this->CellType == 1 )
  {
     output->SetLines(newLines);
     cout << "Setting topology to line" << endl;
  }
  else
  { 
     output->SetVerts(newLines);
     cout << "Setting topology to vertex" << endl;
  }

  newLines->Delete();

  return 1;
}

void vtkChainSource::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
