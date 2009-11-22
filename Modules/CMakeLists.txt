

### Listing of the files used in VesselExtraction
FILE(GLOB SRC_CHIRONMODULES *.cxx *.h)

IF( WIN32 )
   ADD_LIBRARY( ChironModules STATIC ${SRC_CHIRONMODULES} )
ELSE( WIN32 )
   ADD_LIBRARY( ChironModules SHARED ${SRC_CHIRONMODULES} )
ENDIF( WIN32)
