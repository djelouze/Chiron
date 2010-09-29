PROJECT (Chiron)

### The following are needed to avoid warnings. See CMake doc. ######
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)
#####################################################################

# First of all, this a ParaView plugin. It *needs* ParaView...
FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})


SET (LIBRARY_OUTPUT_PATH ${Chiron_BINARY_DIR}/bin
     CACHE
     PATH
     "Single output directory for building all libraries.")

SET (EXECUTABLE_OUTPUT_PATH ${Chiron_BINARY_DIR}/bin
     CACHE
     PATH
     "Single output directory for building all executables.")


INCLUDE_DIRECTORIES (${LIBRARY_OUTPUT_PATH})
INCLUDE_DIRECTORIES (${EXECUTABLE_OUTPUT_PATH})
INCLUDE_DIRECTORIES (${Chiron_SOURCE_DIR}/Algorithms)
INCLUDE_DIRECTORIES (${Chiron_SOURCE_DIR}/Resources)
INCLUDE_DIRECTORIES (${Chiron_SOURCE_DIR}/Modules)
INCLUDE_DIRECTORIES (${Chiron_SOURCE_DIR}/Plugins)

SET( CHIRON_RESOURCES_PATH ${Chiron_SOURCE_DIR}/Resources )
SET( CHIRON_ALGORITHMS_PATH ${Chiron_SOURCE_DIR}/Algorithms )
SET( CHIRON_PLUGINS_PATH ${Chiron_SOURCE_DIR}/Plugins )

MARK_AS_ADVANCED(
    LIBRARY_OUTPUT_PATH
    EXECUTABLE_OUTPUT_PATH
)

SUBDIRS(
    Algorithms
#   Resources
    Plugins
    Modules
)

OPTION( BUILD_DOCUMENTATION
        "Build Doxygen documentation"
        OFF )

IF( BUILD_DOCUMENTATION )
    SUBDIRS(Documentation)
ENDIF( BUILD_DOCUMENTATION )

