find_path(
	EGL_INCLUDE_DIR
	NAMES EGL/egl.h
	PATHS
	"${EGL_INCLUDEDIR}"
)

find_library(
	EGL_LIBRARY
	NAMES EGL
	PATHS
	"${EGL_LIBRARYDIR}"
)

set(
	EGL_INCLUDE_DIRS
	${EGL_INCLUDE_DIR}
)

set(
	EGL_LIBRARIES
	${EGL_LIBRARY}
)

find_package_handle_standard_args(
	EGL
	DEFAULT_MSG
	EGL_INCLUDE_DIR
	EGL_LIBRARY
)

mark_as_advanced(
	EGL_INCLUDE_DIR
	EGL_LIBRARY
)
