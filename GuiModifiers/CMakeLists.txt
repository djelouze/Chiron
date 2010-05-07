### Listing of the files used in chiron GUI modifiers 
FILE(GLOB CHIRONGUIMODIFIERS_HDRS *.h)
FILE(GLOB CHIRONGUIMODIFIERS_CXX *.cxx)

# We need to wrap for Qt stuff such as signals/slots etc. to work correctly.
QT4_WRAP_CPP(CHIRONGUIMODIFIERS_MOC_SRCS ${CHIRONGUIMODIFIERS_HDRS})



IF( WIN32 )
   ADD_LIBRARY( ChironGuiModifiers STATIC 
                ${CHIRONGUIMODIFIERS_MOC_SRCS}
                ${CHIRONGUIMODIFIERS_CXX} )
ELSE( WIN32 )
   ADD_LIBRARY( ChironGuiModifiers SHARED 
                ${CHIRONGUIMODIFIERS_MOC_SRCS}
                ${CHIRONGUIMODIFIERS_CXX} )
ENDIF( WIN32)

