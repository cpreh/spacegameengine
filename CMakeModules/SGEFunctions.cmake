include(
	CMakeParseArguments
)

function(
	sge_link_target
	LIBNAME
)
	if(
		SGE_DEFAULT_LINK_STATIC
	)
		set(
			${LIBNAME}_TARGET
			${LIBNAME}_static
			PARENT_SCOPE
		)
	else()
		set(
			${LIBNAME}_TARGET
			${LIBNAME}
			PARENT_SCOPE
		)
	endif()
endfunction()

macro(
	transform_sge_link_targets
	SGELIBS
	RESULT_VAR
)
	unset(
		${RESULT_VAR}
	)

	foreach(
		CURLIB
		${SGELIBS}
	)
		sge_link_target(
			${CURLIB}
		)

		list(
			APPEND
			${RESULT_VAR}
			"${${CURLIB}_TARGET}"
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
)
	set(
		SINGLE_ARGS
		VARIANT
		BASE_VARIANT
	)

	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		TRANSITIVE_SGE_DEPS
		TRANSITIVE_ADDITIONAL_DEPS
		INCLUDE_DIRS
		TRANSITIVE_INCLUDE_DIRS
		COMPILE_DEFINITIONS
		TRANSITIVE_COMPILE_DEFINITIONS
		COMPILE_FLAGS
	)

	cmake_parse_arguments(
		""
		""
		"${SINGLE_ARGS}"
		"${MULTI_ARGS}"
		${ARGN}
	)

	if(
		${_VARIANT} STREQUAL "STATIC"
	)
		set(
			SGE_LIB_NAME
			"${SGE_LIB_NAME}_static"
		)
	endif()

	add_library(
		${SGE_LIB_NAME}
		${_VARIANT}
		${SGE_LIB_FILES}
	)

	fcppt_utils_set_so_version(
		${SGE_LIB_NAME}
		${SGE_USED_SO_VERSION}
	)

	fcppt_utils_set_target_compiler_flags(
		${SGE_LIB_NAME}
		ADDITIONAL_FLAGS
		"${_COMPILE_FLAGS}"
	)

	fcppt_utils_interface_static_link(
		${SGE_LIB_NAME}
		${_VARIANT}
		"SGE_STATIC_LINK"
	)

	transform_sge_link_targets(
		"${_SGE_DEPS}"
		SGE_DEPS_RESULT
	)

	transform_sge_link_targets(
		"${_TRANSITIVE_SGE_DEPS}"
		TRANSITIVE_SGE_DEPS_RESULT
	)

	target_link_libraries(
		${SGE_LIB_NAME}
		PRIVATE
		${_ADDITIONAL_DEPS}
		${SGE_DEPS_RESULT}
		INTERFACE
		${TRANSITIVE_SGE_DEPS_RESULT}
		${_TRANSITIVE_ADDITIONAL_DEPS}
	)

	target_include_directories(
		${SGE_LIB_NAME}
		PRIVATE
		${_INCLUDE_DIRS}
		INTERFACE
		${_TRANSITIVE_INCLUDE_DIRS}
	)

	target_compile_definitions(
		${SGE_LIB_NAME}
		PRIVATE
		${_COMPILE_DEFINITIONS}
		INTERFACE
		${_TRANSITIVE_COMPILE_DEFINITIONS}
	)

	fcppt_utils_add_target_include_dir(
		${SGE_LIB_NAME}
		TRUE
	)

	#Dummy and example libs should not be exported
	if(
		NOT "${_BASE_VARIANT}" STREQUAL "DUMMY"
		AND
		NOT "${_BASE_VARIANT}" STREQUAL "EXAMPLE"
	)
		fcppt_utils_export_install_target(
			"${SGE_LIB_NAME}"
		)
	# Dynamic example libs still need to be installed,
	# otherwise the examples won't work
	elseif(
		"${_BASE_VARIANT}" STREQUAL "EXAMPLE"
		AND
		NOT "${_VARIANT}" STREQUAL "STATIC"
	)
		install(
			TARGETS
			"${SGE_LIB_NAME}"
			DESTINATION
			"${INSTALL_LIBRARY_DIR}"
		)
	endif()
endfunction()

function(
	add_sge_base_library_base
	RELATIVE_PATH
)
	set(
		SINGLE_ARGS
		BASE_VARIANT
	)

	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		TRANSITIVE_SGE_DEPS
		TRANSITIVE_ADDITIONAL_DEPS
		INCLUDE_DIRS
		TRANSITIVE_INCLUDE_DIRS
		COMPILE_DEFINITIONS
		TRANSITIVE_COMPILE_DEFINITIONS
	)

	cmake_parse_arguments(
		""
		""
		"${SINGLE_ARGS}"
		"${MULTI_ARGS}"
		${ARGN}
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

	check_library_deps(
		"${LIB_NAME}"
		"${_SGE_DEPS}"
	)

	check_library_deps(
		"${LIB_NAME}"
		"${_TRANSITIVE_SGE_DEPS}"
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
		"${_BASE_VARIANT}" STREQUAL "DUMMY"
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
		ENABLE_SHARED
	)
		add_sge_base_library_variant(
			${SGE_LIB_NAME}
			"${SGE_LIB_FILES}"
			VARIANT
			"SHARED"
			${ARGN}
		)
	endif()

	if(
		ENABLE_STATIC
		AND NOT
		"${_BASE_VARIANT}" STREQUAL "DUMMY"
	)
		add_sge_base_library_variant(
			${SGE_LIB_NAME}
			"${SGE_LIB_FILES}"
			VARIANT
			"STATIC"
			${ARGN}
		)
	endif()

	if(
		NOT "${_BASE_VARIANT}" STREQUAL "EXAMPLE"
	)
		get_filename_component(
			DEST_INCLUDE_PATH
			${RELATIVE_PATH}
			PATH
		)

		set(
			SGE_INSTALL_INCLUDE_DIRS
			"${FCPPT_UTILS_PROJECT_SOURCE_DIR}/include/sge/${RELATIVE_PATH}"
		)

		if(
			NOT "${_BASE_VARIANT}" STREQUAL "DUMMY"
		)
			list(
				APPEND
				SGE_INSTALL_INCLUDE_DIRS
				"${FCPPT_UTILS_PROJECT_BINARY_DIR}/include/sge/${RELATIVE_PATH}"
			)
		endif()

		install(
			DIRECTORY
			${SGE_INSTALL_INCLUDE_DIRS}
			DESTINATION
			"${INSTALL_INCLUDE_DIR}/sge/${DEST_INCLUDE_PATH}"
		)
	endif()
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
#
# INCLUDE_DIRS:
#	A list of include directories the library needs to be built.
#
# TRANSITIVE_INCLUDE_DIRS:
#	A list of include directories a consumer of the library needs to be
#	built.
#
# COMPILE_DEFINITIONS:
#	A list of compile definitions to add.
#
# TRANSITIVE_COMPILE_DEFINITIONS:
#	A list of compile definitions other libraries have to use that link to
#	this one.
#
# COMPILE_FLAGS:
#	A list of compile flags to add.
function(
	add_sge_base_library
	RELATIVE_PATH
)
	string(
		REPLACE
		"/"
		""
		LIB_NAME
		"${RELATIVE_PATH}"
	)

	get_property(
		SGE_LIBS
		GLOBAL
		PROPERTY
		"SGE_LIBRARIES_GLOBAL"
	)

	list(
		APPEND
		SGE_LIBS
		"sge${LIB_NAME}"
	)

	set_property(
		GLOBAL
		PROPERTY
		"SGE_LIBRARIES_GLOBAL"
		"${SGE_LIBS}"
	)

	add_sge_base_library_base(
		"${RELATIVE_PATH}"
		BASE_VARIANT
		""
		${ARGN}
	)
endfunction()

# See add_sge_base_library
function(
	add_sge_dummy_library
	RELATIVE_PATH
)
	add_sge_base_library_base(
		"${RELATIVE_PATH}"
		BASE_VARIANT
		"DUMMY"
		${ARGN}
	)
endfunction()

# See add_sge_base_library
function(
	add_sge_example_library
	RELATIVE_PATH
)
	add_sge_base_library_base(
		"${RELATIVE_PATH}"
		BASE_VARIANT
		"EXAMPLE"
		${ARGN}
	)
endfunction()

# TODO: Replace this!
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
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/src/${LIB_NAME}/include
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
		ADDITIONAL_DEPS
		"${fcppt_core_TARGET}"
		VARIANT
		"${VARIANT}"
	)
endfunction()

# add_sge_plugin
#
# Adds an sge plugin
#
# PLUGIN_NAME:
#	The name of the plugin.
#
# SGE_DEPS:
#	A list of sge libraries that this library depends on.
#
# ADDITIONAL_DEPS:
#	A list of additional (not sge) libraries that this library depends on.
#
# INCLUDE_DIRS:
#	A list of include directories the library needs to be built.
#
# COMPILE_DEFINITIONS:
#	A list of compile definitions to add.
#
# COMPILE_FLAGS:
#	A list of compile flags to add.
function(
	add_sge_plugin
	PLUGIN_NAME
)
	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		INCLUDE_DIRS
		COMPILE_DEFINITIONS
		COMPILE_FLAGS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	set(
		SGE_PLUGIN_NAME
		sge${PLUGIN_NAME}
	)

	string(
		TOUPPER
		${PLUGIN_NAME}
		UPPER_PLUGIN_NAME
	)

	fcppt_utils_append_source_dir_and_make_groups(
		"${SGE_${UPPER_PLUGIN_NAME}_FILES}"
		SGE_${UPPER_PLUGIN_NAME}_FILES_ABS
	)

	add_library(
		${SGE_PLUGIN_NAME}
		SHARED
		${SGE_${UPPER_PLUGIN_NAME}_FILES_ABS}
	)

	transform_sge_link_targets(
		"${_SGE_DEPS}"
		SGE_DEPS_RESULT
	)

	check_library_deps(
		"${PLUGIN_NAME}"
		"${_SGE_DEPS}"
	)

	fcppt_utils_set_target_compiler_flags(
		${SGE_PLUGIN_NAME}
		ADDITIONAL_FLAGS
		"${_COMPILE_FLAGS}"
	)

	target_include_directories(
		${SGE_PLUGIN_NAME}
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${_INCLUDE_DIRS}
	)

	target_compile_definitions(
		${SGE_PLUGIN_NAME}
		PRIVATE
		${_COMPILE_DEFINITIONS}
	)

	target_link_libraries(
		${SGE_PLUGIN_NAME}
		PRIVATE
		${_ADDITIONAL_DEPS}
		${SGE_DEPS_RESULT}
	)

	install(
		TARGETS
		${SGE_PLUGIN_NAME}
		DESTINATION
		${PLUGIN_INSTALL_DIR}
	)
endfunction()
