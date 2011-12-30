# - Try to find SGE
#
# This module defines the following variables
#
#	SGE_FOUND                - True if SGE was found.
#	SGE_INCLUDE_DIRS         - All includes required for SGE to work.
#	SGE_DEFINITIONS          - Additional compiler flags required
#	SGE_CORE_LIBRARY         - The core library.
#	SGE_${COMPONENT}_FOUND   - True if the component was found.
#	SGE_${COMPONENT}_LIBRARY - The library for each component requested.
#	SGE_LIBRARIES            - All libraries the user requested (SGE_CORE_LIBRARY + every component).
#
# This module accepts the following variables as input
#
#	SGE_USE_STATIC_LIBS  - Use static linking.
#	SGE_INCLUDEDIR       - Hint where sge's includes might be.
#	SGE_LIBRARYDIR       - Hint where sge's libraries might be.
#

# Find all required packages for SGE.
if(
	SGE_FIND_QUIETLY
)
	set(
		SGE_FIND_OPTIONS
		"QUIET"
	)
endif()

if(
	SGE_FIND_REQUIRED
)
	set(
		SGE_FIND_OPTIONS
		"REQUIRED"
	)
endif()


#Set SGE_DEFINITIONS for static linking
if(
	SGE_USE_STATIC_LIBS
)
	set(
		SGE_DEFINITIONS
		"-D SGE_STATIC_LINK"
	)
endif()

find_package(
	Boost
	1.46.0
	${SGE_FIND_OPTIONS}
)

find_package(
	Fcppt
	${SGE_FIND_OPTIONS}
)

find_package(
	Awl
	${SGE_FIND_OPTIONS}
)

find_package(
	Mizuiro
	${SGE_FIND_OPTIONS}
)

# Find SGE's include dir, take SGE_INCLUDEDIR as a HINT.
find_path(
	SGE_INCLUDE_DIR
	NAMES sge/exception.hpp
	HINTS ${SGE_INCLUDEDIR}
)

# If the include dir was found, set SGE_FOUND to TRUE. It can later be set to
# FALSE again if a COMPONENT is missing.
if(
	SGE_INCLUDE_DIR
)
	set(
		SGE_FOUND
		TRUE
	)
endif()

# Try to find each component.
foreach(
	COMPONENT
	${SGE_FIND_COMPONENTS}
)
	# The library variables will be in upper case.
	string(
		TOUPPER
		${COMPONENT}
		UPPERCOMPONENT
	)

	set(
		SGE_CURRENT_LIB
		SGE_${UPPERCOMPONENT}_LIBRARY
	)

	if(
		SGE_USE_STATIC_LIBS
	)
		set(
			SGE_CURRENT_LIB_NAME
			sge${COMPONENT}_static
		)
	else()
		set(
			SGE_CURRENT_LIB_NAME
			sge${COMPONENT}
		)
	endif()

	# Find the current library.
	find_library(
		${SGE_CURRENT_LIB}
		NAMES ${SGE_CURRENT_LIB_NAME}
		HINTS "${SGE_LIBRARYDIR}"
	)

	# Special cases for SGE libs that require more includes.
	if(
		COMPONENT
		STREQUAL
		cegui
	)
		# CEGUI headers are required for sgecegui.
		find_package(
			CEGUI
			${SGE_FIND_OPTIONS}
		)

		if(
			NOT CEGUI_FOUND
		)
			# Unset ${SGE_CURRENT_LIB} so the rest of the loop behaves properly.
			unset(
				${SGE_CURRENT_LIB}
			)
		else()
			set(
				SGE_INCLUDE_DIRS
				"${SGE_INCLUDE_DIRS};${CEGUI_INCLUDE_DIRS}"
			)
		endif()
	endif()

	set(
		SGE_ALL_VARIABLES
		"${SGE_ALL_VARIABLES};${SGE_CURRENT_LIB}"
	)

	# If the library was not found, set SGE_FOUND to FALSE.
	if(
		NOT ${SGE_CURRENT_LIB}
	)
		set(
			SGE_${UPPERCOMPONENT}_FOUND
			false
		)

		set(
			SGE_FOUND FALSE
		)
	else()
		set(
			SGE_${UPPERCOMPONENT}_FOUND
			true
		)

		set(
			SGE_LIBRARIES
			"${SGE_LIBRARIES};${${SGE_CURRENT_LIB}}"
		)
	endif()
endforeach()

# Accumulate SGE_INCLUDE_DIRS.
if(
	SGE_FOUND
)
	set(
		SGE_INCLUDE_DIRS
		"${SGE_INCLUDE_DIRS};${Boost_INCLUDE_DIRS};${Fcppt_INCLUDE_DIRS};${Awl_INCLUDE_DIRS};${Mizuiro_INCLUDE_DIRS};${SGE_INCLUDE_DIR}"
	)
else()
	unset(
		SGE_INCLUDE_DIRS
	)

	unset(
		SGE_LIBRARIES
	)
endif()

mark_as_advanced(
	SGE_INCLUDE_DIR
)

if(
	SGE_FOUND
)
	if(
		NOT SGE_FIND_QUIETLY
	)
		message(
			STATUS
			"Found SGE: ${SGE_INCLUDE_DIR}"
		)
	endif()
else()
	set(
		SGE_ERROR_MESSAGE
		"Could NOT find SGE (missing: "
	)

	set(
		SGE_ALL_VARIABLES
		"${SGE_ALL_VARIABLES};SGE_CORE_LIBRARY;SGE_INCLUDE_DIR"
	)

	foreach(
		CUR_VARIABLE
		${SGE_ALL_VARIABLES}
	)
		if(
			NOT ${CUR_VARIABLE}
		)
			set(
				SGE_ERROR_MESSAGE
				"${SGE_ERROR_MESSAGE} ${CUR_VARIABLE}"
			)
		endif()
	endforeach()

	if(
		SGE_FIND_REQUIRED
	)
		message(
			SEND_ERROR
			"${SGE_ERROR_MESSAGE})"
		)
	endif()

	unset(
		SGE_ERROR_MESSAGE
	)
endif()

unset(
	SGE_FIND_OPTIONS
)

unset(
	SGE_CURRENT_LIB
)

unset(
	SGE_ALL_VARIABLES
)
