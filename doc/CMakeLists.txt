find_package(Doxygen REQUIRED)

set(DOC_OUTPUT "${FCPPT_UTILS_PROJECT_BINARY_DIR}/doc_generated")

configure_file(Doxyfile.in "${DOC_OUTPUT}/Doxyfile")

# For now, use COPYONLY (since I don't know which escape sequences are in the
# html/css files that cmake might accidentally replace. Could be changed in the
# future.
configure_file(header.html "${DOC_OUTPUT}/header.html" COPYONLY)

configure_file(footer.html "${DOC_OUTPUT}/footer.html" COPYONLY)

configure_file(stylesheet.css "${DOC_OUTPUT}/stylesheet.css" COPYONLY)

configure_file(layout.xml "${DOC_OUTPUT}/layout.xml" COPYONLY)

fcppt_utils_load_source_files(doc/files.txt SGE_DOC_FILES)
fcppt_utils_load_source_files(doc/libs_files.txt SGE_LIBS_FILES)

list(APPEND SGE_DOC_FILES ${SGE_LIBS_FILES})

fcppt_utils_append_source_dir("${SGE_DOC_FILES}" SGE_DOC_FILES_ABS)

set(HTML_INDEX_OUTPUT ${DOC_OUTPUT}/html/index.html)

add_custom_command(
  OUTPUT "${HTML_INDEX_OUTPUT}"
  COMMAND ${DOXYGEN_EXECUTABLE}
  DEPENDS ${SGE_DOC_FILES_ABS}
  WORKING_DIRECTORY "${DOC_OUTPUT}")

add_custom_target(doc ALL SOURCES ${HTML_INDEX_OUTPUT})

install(DIRECTORY "${DOC_OUTPUT}/html" DESTINATION "${CMAKE_INSTALL_DOCDIR}")
