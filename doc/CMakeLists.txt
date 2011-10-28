find_package(
	Doxygen
	REQUIRED
)

set(
	DOC_OUTPUT
	"${CMAKE_BINARY_DIR}/doc_generated"
)

configure_file(
	Doxyfile.in
	"${DOC_OUTPUT}/Doxyfile"
)

add_custom_target(
	doc
)

add_custom_command(
	TARGET doc
	COMMAND ${DOXYGEN_EXECUTABLE}
	WORKING_DIRECTORY "${DOC_OUTPUT}"
)

install(
	DIRECTORY
	"${DOC_OUTPUT}/html"
	DESTINATION
	"${INSTALL_DOC_DIR}"
)
