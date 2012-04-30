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

if(
	WIN32
)
	if(
		CMAKE_SIZEOF_VOID_P EQUAL 8
	)
		set(
			CG_LIB_ENV
			"CG_LIB64_PATH"
		)
	elseif(
		CMAKE_SIZEOF_VOID_P EQUAL 4
	)
		set(
			CG_LIB_ENV
			"CG_LIB_PATH"
		)
	endif()

	set(
		CG_HINTED_LIBRARY_DIR
		"$ENV{${CG_LIB_ENV}}"
	)

	set(
		CG_HINTED_INCLUDE_DIR
		"$ENV{CG_INC_PATH}"
	)
else()
	set(
		Cg_ROOT
		"/opt/nvidia-cg-toolkit"
	)

	set(
		CG_HINTED_LIBRARY_DIR
		${Cg_ROOT}/lib
	)

	set(
		CG_HINTED_INCLUDE_DIR
		${Cg_ROOT}/include
	)
endif()

find_path(
	Cg_INCLUDE_DIR
	NAMES Cg/cg.h
	HINTS
	"${CG_HINTED_INCLUDE_DIR}"
	PATHS
	"${CG_INCLUDEDIR}"
)

find_library(
	Cg_LIBRARY
	NAMES Cg
	HINTS
	"${CG_HINTED_LIBRARY_DIR}"
	PATHS
	"${CG_LIBRARYDIR}"
)

find_library(
	Cg_GL_LIBRARY
	NAMES CgGL
	HINTS
	"${CG_HINTED_LIBRARY_DIR}"
	PATHS
	"${CG_LIBRARYDIR}"
)

find_library(
	Cg_D3D9_LIBRARY
	NAMES CgD3D9
	HINTS
	"${CG_HINTED_LIBRARY_DIR}"
	PATHS
	"${CG_LIBRARYDIR}"
)

set(
	Cg_INCLUDE_DIRS
	${Cg_INLUDE_DIR}
)

set(
	Cg_LIBRARIES
	${Cg_LIBRARY}
)

set(
	Cg_GL_LIBRARIES
	"${Cg_GL_LIBRARY}"
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
	CG_HINTED_LIBRARY_DIR
	CG_HINTED_INCLUDE_DIR
)
