function(
	sge_set_static_flags
	TARGETNAME
)
	set_target_properties(
		${TARGETNAME}
		PROPERTIES
		COMPILE_DEFINITIONS
		"SGE_STATIC_LINK"
	)
endfunction()

macro(
	sge_link_target
	LIBNAME
)
	if(
		SGE_DEFAULT_LINK_STATIC
	)
		set(
			${LIBNAME}_TARGET
			${LIBNAME}_static
		)
	else()
		set(
			${LIBNAME}_TARGET
			${LIBNAME}
		)
	endif()
endmacro()

macro(
	transform_sge_link_targets
	SGELIBS
)
	unset(
		SGELIBS_TARGETS_RESULT
	)

	foreach(
		CURLIB
		${SGELIBS}
	)
		sge_link_target(
			${CURLIB}
		)

		set(
			SGELIBS_TARGETS_RESULT
			"${SGELIBS_TARGETS_RESULT};${${CURLIB}_TARGET}"
		)
	endforeach()
endmacro()

function(
	check_library_deps
	LIB_NAME
	ADDITONAL_DEPS
)
	foreach(
		DEPENDENCY
		${ADDITONAL_DEPS}
	)
		string(
			REPLACE
			"sge"
			""
			SUFFIX
			${DEPENDENCY}
		)

		string(
			TOUPPER
			${SUFFIX}
			UPPER_SUFFIX
		)

		if(
			NOT ${UPPER_SUFFIX} STREQUAL "CORE"
			AND NOT ENABLE_${UPPER_SUFFIX}
		)
			message(
				FATAL_ERROR
				"For ${LIB_NAME} to work you need to -D ENABLE_${UPPER_SUFFIX}=ON!"
			)
		endif()
	endforeach()
endfunction()

function(
	sge_generate_symbol_header
	EXPORTS_NAME
	SYMBOL_NAME
	RELATIVE_PATH
)
	fcppt_generate_symbol_header(
		"SGE_STATIC_LINK"
		"${EXPORTS_NAME}"
		"${SYMBOL_NAME}"
		"${RELATIVE_PATH}"
	)
endfunction()

function(
	sge_generate_instantiate_symbol_header
	LIB_NAME
)
	string(
		TOUPPER
		"${LIB_NAME}"
		UPPER_LIB_NAME
	)

	set(
		SYMBOL_NAME
		"SGE_${UPPER_LIB_NAME}_DETAIL_INSTANTIATE"
	)

	sge_generate_symbol_header(
		"${SYMBOL_NAME}"
		"${SYMBOL_NAME}"
		"sge/${LIB_NAME}/detail/instantiate"
	)
endfunction()

function(
	add_sge_base_library_variant
	SGE_LIB_NAME
	SGE_LIB_FILES
	SGE_DEPS
	ADDITIONAL_DEPS
	TRANSITIVE_SGE_DEPS
	TRANSITIVE_ADDITIONAL_DEPS
	VARIANT
)
	if(
		${VARIANT} STREQUAL "STATIC"
	)
		set(
			SGE_LIB_NAME
			"${SGE_LIB_NAME}_static"
		)
	endif()

	if(
		${VARIANT} STREQUAL "DUMMY"
	)
		set(
			LIBRARY_VARIANT
			SHARED
		)
	else()
		set(
			LIBRARY_VARIANT
			${VARIANT}
		)
	endif()

	add_library(
		${SGE_LIB_NAME}
		${LIBRARY_VARIANT}
		${SGE_LIB_FILES}
	)

	if(
		${VARIANT} STREQUAL "STATIC"
	)
		sge_set_static_flags(
			${SGE_LIB_NAME}
		)
	endif()

	transform_sge_link_targets(
		"${SGE_DEPS}"
	)

	target_link_libraries(
		${SGE_LIB_NAME}
		${ADDITIONAL_DEPS}
		${SGELIBS_TARGETS_RESULT}
	)

	set_target_properties(
		${SGE_LIB_NAME}
		PROPERTIES
		LINK_INTERFACE_LIBRARIES
		""
	)

	target_link_libraries(
		${SGE_LIB_NAME}
		LINK_INTERFACE_LIBRARIES
		${TRANSITIVE_SGE_DEPS}
		${TRANSITIVE_ADDITIONAL_DEPS}
	)

	if(
		NOT ${VARIANT} STREQUAL "DUMMY"
	)
		install(
			TARGETS
			${SGE_LIB_NAME}
			DESTINATION
			${INSTALL_LIBRARY_DIR}
		)
	endif()
endfunction()

function(
	add_sge_base_library_base
	RELATIVE_PATH
	SGE_DEPS
	ADDITIONAL_DEPS
	TRANSITIVE_SGE_DEPS
	TRANSITIVE_ADDITIONAL_DEPS
	IS_DUMMY
)
	string(
		REPLACE
		"/"
		""
		LIB_NAME
		"${RELATIVE_PATH}"
	)

	string(
		TOUPPER
		${LIB_NAME}
		UPPER_LIB_NAME
	)

	set(
		SGE_LIB_NAME
		sge${LIB_NAME}
	)

	fcppt_utils_append_source_dir_and_make_groups(
		"${SGE_${UPPER_LIB_NAME}_FILES}"
		SGE_${UPPER_LIB_NAME}_FILES_ABS
	)

	set(
		SGE_LIB_FILES
		${SGE_${UPPER_LIB_NAME}_FILES_ABS}
	)

	if(
		"${IS_DUMMY}" STREQUAL "DUMMY"
	)
		set(
			SGE_DUMMY_SOURCE_FILE
			"${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp"
		)

		if(
			NOT SGE_${UPPER_LIB_NAME}_DUMMY_GENERATED
		)
			file(
				WRITE
				"${SGE_DUMMY_SOURCE_FILE}"
				""
			)
		endif()

		set(
			SGE_${UPPER_LIB_NAME}_DUMMY_GENERATED
			TRUE
			CACHE
			INTERNAL
			""
		)

		list(
			APPEND
			SGE_LIB_FILES
			"${SGE_DUMMY_SOURCE_FILE}"
		)
	else()
		string(
			REPLACE
			"/"
			"_"
			SGE_LIB_SYMBOL
			"${RELATIVE_PATH}"
		)

		string(
			TOUPPER
			"${SGE_LIB_SYMBOL}"
			SGE_LIB_SYMBOL
		)

		sge_generate_symbol_header(
			"${SGE_LIB_NAME}"
			"SGE_${SGE_LIB_SYMBOL}"
			"sge/${RELATIVE_PATH}"
		)
	endif()

	if(
		"${IS_DUMMY}" STREQUAL "DUMMY"
	)
		add_sge_base_library_variant(
			${SGE_LIB_NAME}
			"${SGE_LIB_FILES}"
			"${SGE_DEPS}"
			"${ADDITIONAL_DEPS}"
			"${TRANSITIVE_SGE_DEPS}"
			"${TRANSITIVE_ADDITIONAL_DEPS}"
			DUMMY
		)
	else()
		if(
			ENABLE_SHARED
		)
			add_sge_base_library_variant(
				${SGE_LIB_NAME}
				"${SGE_LIB_FILES}"
				"${SGE_DEPS}"
				"${ADDITIONAL_DEPS}"
				"${TRANSITIVE_SGE_DEPS}"
				"${TRANSITIVE_ADDITIONAL_DEPS}"
				SHARED
			)
		endif()

		if(
			ENABLE_STATIC
		)
			add_sge_base_library_variant(
				${SGE_LIB_NAME}
				"${SGE_LIB_FILES}"
				"${SGE_DEPS}"
				"${ADDITIONAL_DEPS}"
				"${TRANSITIVE_SGE_DEPS}"
				"${TRANSITIVE_ADDITIONAL_DEPS}"
				STATIC
			)
		endif()
	endif()

	check_library_deps(
		"${LIB_NAME}"
		"${SGE_DEPS}"
	)

	check_library_deps(
		"${LIB_NAME}"
		"${TRANSITIVE_SGE_DEPS}"
	)

	get_filename_component(
		DEST_INCLUDE_PATH
		${RELATIVE_PATH}
		PATH
	)

	install(
		DIRECTORY
		${CMAKE_SOURCE_DIR}/include/sge/${RELATIVE_PATH}
		${CMAKE_BINARY_DIR}/include/sge/${RELATIVE_PATH}
		DESTINATION
		${INSTALL_INCLUDE_DIR}/sge/${DEST_INCLUDE_PATH}
	)
endfunction()

# add_sge_base_library
#
# Adds an sge library (not a plugin)
#
# RELATIVE_PATH:
#	The path of the library including its name. / characters denote
#	subdirectories and will be stripped from the library name.
#
# SGE_DEPS:
#	A list of sge libraries that this library depends on.
#
# ADDITIONAL_DEPS:
#	A list of additional (not sge) libraries that this library depends on.
#
# TRANSITIVE_SGE_DEPS:
#	A list of sge libraries that other libraries that will use this library
#	depend on, for example, if this library uses another library in
#	template or inline code.
#
# TRANSITIVE_ADDITIONAL_DEPS:
#	A list of additional (not sge) libraries that other libraries that use
#	this library depend on.
function(
	add_sge_base_library
	RELATIVE_PATH
	SGE_DEPS
	ADDITIONAL_DEPS
	TRANSITIVE_SGE_DEPS
	TRANSITIVE_ADDITIONAL_DEPS
)
	add_sge_base_library_base(
		"${RELATIVE_PATH}"
		"${SGE_DEPS}"
		"${ADDITIONAL_DEPS}"
		"${TRANSITIVE_SGE_DEPS}"
		"${TRANSITIVE_ADDITIONAL_DEPS}"
		""
	)
endfunction()

function(
	add_sge_dummy_library
	RELATIVE_PATH
	SGE_DEPS
	ADDITIONAL_DEPS
	TRANSITIVE_SGE_DEPS
	TRANSITIVE_ADDITIONAL_DEPS
)
	add_sge_base_library_base(
		"${RELATIVE_PATH}"
		"${SGE_DEPS}"
		"${ADDITIONAL_DEPS}"
		"${TRANSITIVE_SGE_DEPS}"
		"${TRANSITIVE_ADDITIONAL_DEPS}"
		"DUMMY"
	)
endfunction()

macro(
	sge_implement_from_lib
	LIB_NAME
)
	string(
		TOUPPER
		${LIB_NAME}
		UPPER_LIB_NAME
	)

	add_definitions(
		"-D SGE_${UPPER_LIB_NAME}_DETAIL_INSTANTIATE_EXPORTS"
	)

	include_directories(
		${CMAKE_SOURCE_DIR}/src/${LIB_NAME}/include
	)
endmacro()

function(
	add_sge_core_lib
	VARIANT
)
	set(
		SGE_CORE_FILES
		"${SGE_CORE_INCLUDE_FILES_ABS};${SGE_CORE_SRC_FILES_ABS}"
	)

	add_sge_base_library_variant(
		sgecore
		"${SGE_CORE_FILES}"
		""
		"${Fcppt_core_LIBRARIES}"
		""
		""
		${VARIANT}
	)
endfunction()


