##    Copyright Jerome Velut 2010
##
##    This file is part of Chiron.
##
##    Chiron is free software: you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation, either version 3 of the License, or
##    (at your option) any later version.
##
##    Chiron is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You have received a copy of the GNU General Public License
##    along with Chiron in the file COPYING.  
##    If not, see <http:##www.gnu.org/licenses/>.

### Find VTK
INCLUDE (${CMAKE_ROOT}/Modules/FindVTK.cmake)
IF (USE_VTK_FILE)
  INCLUDE(${USE_VTK_FILE})
ENDIF (USE_VTK_FILE)

### Listing of the files used in VesselExtraction
FILE(GLOB SRC_CHIRON_ALGO *.cxx *.h)

### Defines VesselExtractionVTK lib an links
IF( WIN32 )
   ADD_LIBRARY( ChironAlgo STATIC ${SRC_CHIRON_ALGO} )
ELSE( WIN32 )
   ADD_LIBRARY( ChironAlgo SHARED ${SRC_CHIRON_ALGO} )
ENDIF( WIN32)

TARGET_LINK_LIBRARIES( ChironAlgo vtkIO
vtkFiltering vtkRendering vtkGraphics vtkImaging vtkHybrid)

