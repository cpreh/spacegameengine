# - Try to find Direct3D 9
# This module defines the following variables
#
#	D3D9_FOUND - True when Direct Input was found
#	D3D9_INCLUDE_DIR - Include directory for Direct Input
#	D3D9_LIBRARIES - Libraries to link to
#	D3D9_LIBRARY_DIR - Library path for all Direct Input libraries
# Note that only the x86 version will be searched for right now

FIND_PATH(
	D3D9_INCLUDE_DIR
	d3d9.h
	"$ENV{DXSDK_DIR}/Include"
)

IF(
	NOT D3D9_LIBRARY_DIR
)
	IF(
		CMAKE_SIZEOF_VOID_P EQUAL 8
	)
		SET(D3D9_LIBRARY_DIR "$ENV{DXSDK_DIR}/Lib/x64")
	ELSEIF(
		CMAKE_SIZEOF_VOID_P EQUAL 4 
	)
		SET(D3D9_LIBRARY_DIR "$ENV{DXSDK_DIR}/Lib/x86")
	ENDIF()
ENDIF()

FIND_LIBRARY(
	D3D9_LIBRARY
	NAMES d3d9
	PATHS
	"${D3D9_LIBRARY_DIR}"
)

INCLUDE(
	FindPackageHandleStandardArgs
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	D3D9
	DEFAULT_MSG
	D3D9_INCLUDE_DIR
	D3D9_LIBRARY
)

IF(
	D3D9_FOUND
)
	SET(D3D9_LIBRARIES "${D3D9_LIBRARY}")
ENDIF()

MARK_AS_ADVANCED(
	D3D9_INCLUDE_DIR
	D3D9_LIBRARY
)
