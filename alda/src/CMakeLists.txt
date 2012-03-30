set(
	ALDA_FILES
	alda/src/exception.cpp
)

fcppt_generate_symbol_header(
	"ALDA_STATIC_LINK"
	"alda"
	"ALDA"
	"alda"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

function(
	add_alda_library
	VARIANT
)
	if(
		${VARIANT} STREQUAL "STATIC"
	)
		set(
			ALDA_LIB_NAME
			"alda_static"
		)
	else()
		set(
			ALDA_LIB_NAME
			"alda"
		)
	endif()

	fcppt_utils_append_source_dir_and_make_groups(
		"${ALDA_FILES}"
		ALDA_FILES_ABS
	)

	add_library(
		${ALDA_LIB_NAME}
		${VARIANT}
		${ALDA_FILES_ABS}
	)

	set_target_properties(
		${ALDA_LIB_NAME}
		PROPERTIES
		LINK_INTERFACE_LIBRARIES
		""
	)

	install(
		TARGETS
		${ALDA_LIB_NAME}
		DESTINATION
		${INSTALL_LIBRARY_DIR}
	)
endfunction()

function(
	alda_set_static_flags
	TARGETNAME
)
	if(
		ALDA_DEFAULT_LINK_TARGET
		STREQUAL
		"alda_static"
	)
		set_target_properties(
			${TARGETNAME}
			PROPERTIES
			COMPILE_DEFINITIONS
			"ALDA_STATIC_LINK"
		)
	endif()
endfunction()

if(
	ENABLE_SHARED
)
	add_alda_library(
		"SHARED"
	)
endif()

if(
	ENABLE_STATIC
)
	add_alda_library(
		"STATIC"
	)
endif()

install(
	DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/include/alda
	DESTINATION
	${INSTALL_INCLUDE_DIR}
)
