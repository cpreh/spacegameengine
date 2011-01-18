# - Try to find DirectInput8
# This module defines the following variables
#
#	DINPUT_FOUND - True when Direct Input was found
#	DINPUT_INCLUDE_DIR - Include directory for Direct Input
#	DINPUT_LIBRARIES - Libraries to link to
#	DINPUT_LIBRARY_DIR - Library path for all Direct Input libraries
# Note that only the x86 version will be searched for right now

FIND_PATH(
	DINPUT_INCLUDE_DIR
	dinput.h
	"$ENV{DXSDK_DIR}/Include"
)

IF(
	NOT DINPUT_LIBRARY_DIR
)
	IF(
		CMAKE_SIZEOF_VOID_P EQUAL 8
	)
		SET(DINPUT_LIBRARY_DIR "$ENV{DXSDK_DIR}/Lib/x64")
	ELSEIF(
		CMAKE_SIZEOF_VOID_P EQUAL 4 
	)
		SET(DINPUT_LIBRARY_DIR "$ENV{DXSDK_DIR}/Lib/x86")
	ENDIF()
ENDIF()

FIND_LIBRARY(
	DINPUT_LIBRARY
	NAMES dinput dinput8
	PATHS
	"${DINPUT_LIBRARY_DIR}"
)

FIND_LIBRARY(
	DXGUID_LIBRARY
	NAMES dxguid
	PATHS
	"${DINPUT_LIBRARY_DIR}"
)

INCLUDE(
	FindPackageHandleStandardArgs
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	DINPUT
	DEFAULT_MSG
	DINPUT_INCLUDE_DIR
	DINPUT_LIBRARY
	DXGUID_LIBRARY
)

IF(
	DINPUT_FOUND
)
	SET(DINPUT_LIBRARIES "${DXGUID_LIBRARY}" "${DINPUT_LIBRARY}")
ENDIF()

MARK_AS_ADVANCED(
	DINPUT_INCLUDE_DIR
	DINPUT_LIBRARY
	DXGUID_LIBRARY
)
