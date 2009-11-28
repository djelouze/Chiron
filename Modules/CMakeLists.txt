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
 

### Listing of the files used in chiron modules 
FILE(GLOB CHIRONMODULES_HDRS *.h)
FILE(GLOB CHIRONMODULES_CXX *.cxx)

# We need to wrap for Qt stuff such as signals/slots etc. to work correctly.
QT4_WRAP_CPP(CHIRONMODULES_MOC_SRCS ${CHIRONMODULES_HDRS})



IF( WIN32 )
   ADD_LIBRARY( ChironModules STATIC 
                ${CHIRONMODULES_MOC_SRCS}
                ${CHIRONMODULES_CXX} )
ELSE( WIN32 )
   ADD_LIBRARY( ChironModules SHARED 
                ${CHIRONMODULES_MOC_SRCS}
                ${CHIRONMODULES_CXX} )
ENDIF( WIN32)
