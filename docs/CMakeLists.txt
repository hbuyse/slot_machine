# check if Doxygen is installed
find_package(Doxygen)
if(DOXYGEN_FOUND)
  execute_process(COMMAND git
                          rev-parse
                          --short
                          HEAD
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  OUTPUT_VARIABLE GIT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE)

  # request to configure the file
  configure_file(${CMAKE_SOURCE_DIR}/docs/Doxyfile.cfg.cmake
                 ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.cfg @ONLY)

  # note the option ALL which allows to build the docs together with the
  # application
  add_custom_target(doc
                    COMMAND ${DOXYGEN_EXECUTABLE}
                            ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.cfg
                            ${DOXYGEN_OUT}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM)
endif(DOXYGEN_FOUND)
