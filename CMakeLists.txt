#    Copyright Jerome Velut 2009
#
#    This file is part of Chiron.
#
#    Chiron is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Chiron is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You have received a copy of the GNU General Public License
#    along with Chiron in the file COPYING.  
#    If not, see <http://www.gnu.org/licenses/>.

PROJECT (Chiron)

### The following are needed to avoid warnings. See CMake doc. ######
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
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
#INCLUDE_DIRECTORIES (${Chiron_SOURCE_DIR}/Algorithms) 
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
#   Algorithms
   Resources
   Plugins
   Modules
)

OPTION( BUILD_DOCUMENTATION 
        "Build Doxygen documentation"
        OFF )

IF( BUILD_DOCUMENTATION )
   SUBDIRS(Documentation)
ENDIF( BUILD_DOCUMENTATION )

