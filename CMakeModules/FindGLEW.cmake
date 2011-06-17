# - Try to find GLEW library and include path.
#
# This module defines the following variables
#
# 	GLEW_FOUND
#	GLEW_DEFINITIONS
# 	GLEW_INCLUDE_DIRS
# 	GLEW_LIBRARRIES
#
# This module accepts the following variables as input
#
#	GLEW_WANT_STATIC_LINK
#	GLEW_INCLUDEDIR
#	GLEW_LIBRARYDIR

find_path(
	GLEW_INCLUDE_DIR
	NAMES GL/glew.h
	HINTS ${GLEW_INCLUDEDIR}
)

if(
	WIN32
)
	if(
		GLEW_WANT_STATIC_LINK
	)
		set(
			GLEW_NAMES "glew32s"
		)
	else()
		set(
			GLEW_NAMES "glew32"
		)
	endif()
else()
	set(
		GLEW_NAMES "GLEW"
	)
endif()

if(
	GLEW_WANT_STATIC_LINK
)
	set(
		GLEW_DEFINITIONS "-D GLEW_STATIC"
	)
endif()

find_library(
	GLEW_LIBRARY
	NAMES ${GLEW_NAMES}
	PATHS ${GLEW_LIBRARYDIR}
)

include(
	FindPackageHandleStandardArgs
)

unset(
	GLEW_NAMES
)

find_package_handle_standard_args(
	GLEW
	DEFAULT_MSG
	GLEW_INCLUDE_DIR
	GLEW_LIBRARY
)

set(
	GLEW_INCLUDE_DIRS
	"${GLEW_INCLUDE_DIR}"
)

set(
	GLEW_LIBRARIES
	"${GLEW_LIBRARY}"
)
