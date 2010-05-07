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
ADD_PARAVIEW_PLUGIN(Chiron "1.0"
                    GUI_INTERFACES ${CHIRON_TOOLBAR_IFACES}
                    SOURCES ${CHIRON_TOOLBAR_MOC_SRCS}
                            ${CHIRON_TOOLBAR_IFACE_SRCS} 
                            ChironToolbarActions.cxx
                    GUI_RESOURCES ${CHIRON_RESOURCES_PATH}/chiron.qrc
                    GUI_RESOURCE_FILES ${CHIRON_RESOURCES_PATH}/chironGUI.xml
                    SERVER_MANAGER_XML ${CHIRON_ALGORITHMS_PATH}/vtkChainSource.xml
                                       ${CHIRON_RESOURCES_PATH}/chiron.xml  #<-- server manager xml
                    SERVER_MANAGER_SOURCES ${CHIRON_ALGORITHMS_PATH}/vtkChainSource.cxx 
                    )

TARGET_LINK_LIBRARIES( Chiron ChironModules )

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
