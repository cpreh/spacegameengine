if(
	Cg_FIND_QUIETLY
)
	set(
		CG_FIND_OPTIONS
		"QUIET"
	)
endif()

if(
	Cg_FIND_REQUIRED
)
	set(
		CG_FIND_OPTIONS
		"REQUIRED"
	)
endif()

# Setup default paths
if(
	WIN32
)
	# TODO:
else()
	set(
		Cg_ROOT
		"/opt/nvidia-cg-toolkit"
	)
endif()

find_path(
	Cg_INCLUDE_DIR
	NAMES Cg/cg.h
	HINTS ${CG_INCLUDEDIR}
	PATHS ${Cg_ROOT}/include
)

find_library(
	Cg_LIBRARY
	NAMES Cg
	HINTS ${CG_LIBRARYDIR}
	PATHS ${Cg_ROOT}/lib
)

set(
	Cg_INCLUDE_DIRS
	${Cg_INLUDE_DIR}
)

set(
	Cg_LIBRARIES
	${Cg_LIBRARY}
)

include(
	FindPackageHandleStandardArgs
)

find_package_handle_standard_args(
	Cg
	DEFAULT_MSG
	Cg_INCLUDE_DIR
	Cg_LIBRARY
)

mark_as_advanced(
	Cg_INCLUDE_DIR
	Cg_LIBRARY
)
