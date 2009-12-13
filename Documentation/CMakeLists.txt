# \todo Doxyfile INPUT field has to be manually set to the correct input path.
# CMake should be able to do this automatically.

# Build the documentation
FIND_PACKAGE(Doxygen)
EXECUTE_PROCESS( COMMAND ${DOXYGEN_EXECUTABLE}
"${Chiron_SOURCE_DIR}/Documentation/Doxyfile"
                 WORKING_DIRECTORY "${Chiron_BINARY_DIR}/Documentation"
                 OUTPUT_FILE doxylog
                 ERROR_FILE doxyerrorlog
                 OUTPUT_QUIET
                 ERROR_QUIET
               )
