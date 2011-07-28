find_path(
	CEGUI_INCLUDE_DIR
	NAMES CEGUI.h
	PATHS /usr/include/CEGUI
	HINTS ${CEGUI_INCLUDEDIR}
)

find_library(
	CEGUI_LIBRARY
	NAMES CEGUIBase
	HINTS ${CEGUI_LIBRARYDIR}
)

mark_as_advanced(
	CEGUI_INCLUDE_DIR
	CEGUI_LIBRARY_DIR
)

include(
	FindPackageHandleStandardArgs
)

set(
	CEGUI_INCLUDE_DIRS
	"${CEGUI_INCLUDE_DIR}"
)

set(
	CEGUI_LIBRARIES
	"${CEGUI_LIBRARY}"
)

find_package_handle_standard_args(
	CEGUI
	DEFAULT_MSG
	CEGUI_INCLUDE_DIR
	CEGUI_LIBRARY
)
