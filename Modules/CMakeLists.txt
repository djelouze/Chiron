### Listing of the files used in chiron modules
FILE(GLOB CHIRONMODULES_HDRS *.h)
FILE(GLOB CHIRONMODULES_CXX *.cxx)

# We need to wrap for Qt stuff such as signals/slots etc. to work correctly.
QT4_WRAP_CPP(CHIRONMODULES_MOC_SRCS ${CHIRONMODULES_HDRS})



ADD_LIBRARY( ChironModules SHARED
               ${CHIRONMODULES_MOC_SRCS}
               ${CHIRONMODULES_CXX} 
)
