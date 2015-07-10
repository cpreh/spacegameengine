# - Try to find DirectInput8
# This module defines the following variables
#
#	DINPUT_FOUND - True when Direct Input was found
#	DINPUT_INCLUDE_DIRS - Include directory for Direct Input
#	DINPUT_LIBRARIES - Libraries to link to

find_path(
	DINPUT_INCLUDE_DIR
	dinput.h
	HINTS
	"${DINPUT_INCLUDEDIR}"
	PATHS
	"$ENV{DXSDK_DIR}/Include"
)

if(
	CMAKE_SIZEOF_VOID_P EQUAL 8
)
	set(
		DINPUT_LIBRARY_ENV_DIR
		"$ENV{DXSDK_DIR}/Lib/x64"
	)
elseif(
	CMAKE_SIZEOF_VOID_P EQUAL 4
)
	set(
		DINPUT_LIBRARY_ENV_DIR
		"$ENV{DXSDK_DIR}/Lib/x86"
	)
endif()

find_library(
	DINPUT_LIBRARY
	NAMES dinput8
	HINTS
	"${DINPUT_LIBRARYDIR}"
	PATHS
	"${DINPUT_LIBRARY_ENV_DIR}"
)

find_library(
	DXGUID_LIBRARY
	NAMES dxguid
	HINTS
	"${DINPUT_LIBRARYDIR}"
	PATHS
	"${DINPUT_LIBRARY_ENV_DIR}"
)

include(
	FindPackageHandleStandardArgs
)

find_package_handle_standard_args(
	DINPUT
	DEFAULT_MSG
	DINPUT_INCLUDE_DIR
	DINPUT_LIBRARY
	DXGUID_LIBRARY
)

if(
	DINPUT_FOUND
)
	set(
		DINPUT_LIBRARIES
		"${DXGUID_LIBRARY}"
		"${DINPUT_LIBRARY}"
	)

	set(
		DINPUT_INCLUDE_DIRS
		"${DINPUT_INCLUDE_DIR}"
	)
endif()

mark_as_advanced(
	DINPUT_INCLUDE_DIR
	DINPUT_LIBRARY
	DXGUID_LIBRARY
)
