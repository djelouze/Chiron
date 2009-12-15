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

