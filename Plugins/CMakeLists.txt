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
 
# TOOLBARS PLUGIN --------------------------------------------------

# We need to wrap for Qt stuff such as signals/slots etc. to work correctly.
QT4_WRAP_CPP(CHIRON_TOOLBAR_MOC_SRCS ChironToolbarActions.h)

# This is a macro for adding QActionGroup subclasses automatically as toolbars.
ADD_PARAVIEW_ACTION_GROUP(CHIRON_TOOLBAR_IFACES 
                          CHIRON_TOOLBAR_IFACE_SRCS 
                          CLASS_NAME ChironToolbarActions
                          GROUP_NAME "ToolBar/Chiron")

# Now create a plugin for the toolbar. Here we pass CHIRON_TOOLBAR_IFACES and 
# CHIRON_TOOLBAR_IFACE_SRCS which are filled up by the above macro with relevant
# entries.
ADD_PARAVIEW_PLUGIN(ChironToolbar "0.1"
                    GUI_INTERFACES ${CHIRON_TOOLBAR_IFACES}
                    SOURCES ${CHIRON_TOOLBAR_MOC_SRCS}
                            ${CHIRON_TOOLBAR_IFACE_SRCS} 
                            ChironToolbarActions.cxx
                    GUI_RESOURCES ${CHIRON_RESOURCES_PATH}/chiron.qrc
                    REQUIRED_PLUGINS ChironAlgoPlugin
                    )

TARGET_LINK_LIBRARIES( ChironToolbar ChironModules )

#------------------------------------------------------------------

# READERS PLUGIN --------------------------------------------------

  # Expose the DICOM Reader to ParaView
 ADD_PARAVIEW_PLUGIN(
   ChironReaders          #<--Name for the plugin
  "1.0"                        #<--Version string
   SERVER_MANAGER_XML ${CHIRON_RESOURCES_PATH}/chiron.xml  #<-- server manager xml
   GUI_RESOURCE_FILES ${CHIRON_RESOURCES_PATH}/chironGUI.xml
 )

# ALGO PLUGIN --------------------------------------------------

 ADD_PARAVIEW_PLUGIN(
   ChironAlgoPlugin          #<--Name for the plugin
  "1.0"                        #<--Version string
   SERVER_MANAGER_XML ${CHIRON_ALGORITHMS_PATH}/vtkChainSource.xml  #<-- server manager xml
   SERVER_MANAGER_SOURCES ${CHIRON_ALGORITHMS_PATH}/vtkChainSource.cxx 
)


TARGET_LINK_LIBRARIES( ChironAlgoPlugin ChironAlgo )
