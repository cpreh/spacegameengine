# - Try to find the mizuiro library
#
# This module defines the following variables
#
#	MIZUIRO_FOUND        - True when mizuiro was found
#	MIZUIRO_INCLUDE_DIRS - The path to the MIZUIRO header files
#
# This modules accepts the following variables
#
#	MIZUIRO_ROOT - can be set to the path containing the mizuiro library files
#		this module will search in the standard include
#		and ${MIZUIRO_ROOT}/include for header files
#

IF (NOT MIZUIRO_ROOT)
	SET( MIZUIRO_ROOT CACHE PATH "" )
ENDIF ()

FIND_PATH(
	MIZUIRO_INCLUDE_DIRS
	NAMES mizuiro/config.hpp
	HINTS ${MIZUIRO_ROOT}/include
)

MARK_AS_ADVANCED(
	MIZUIRO_INCLUDE_DIRS
)
