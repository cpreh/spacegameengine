include(
	FcpptCMakeUtils
)

include(
	CMakeParseArguments
)

# configure some resource paths
set(
	SGE_PLUGIN_BUILD_PATH
	"${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/plugins"
)

function(
	transform_sge_link_targets
	SGELIBS
	RESULT_VAR
)
	foreach(
		CURLIB
		${SGELIBS}
	)
		fcppt_utils_link_target(
			${CURLIB}
		)

		string(
			FIND
			${CURLIB}
			"_interface"
			INTERFACE_POS
		)

		if(
			${INTERFACE_POS}
			EQUAL
			-1
		)
			set(
				TARGET_NAME
				"${${CURLIB}_TARGET}"
			)
		else()
			set(
				TARGET_NAME
				${CURLIB}
			)
		endif()

		list(
			APPEND
			RESULT
			${TARGET_NAME}
		)
	endforeach()

	set(
		${RESULT_VAR}
		${RESULT}
		PARENT_SCOPE
	)
endfunction()

function(
	libname_to_enable_var
	OUT
	LIBNAME
)
	string(
		REPLACE
		"sge"
		""
		RESULT
		${LIBNAME}
	)

	string(
		REPLACE
		"_interface"
		""
		RESULT
		${RESULT}
	)

	string(
		TOUPPER
		"${RESULT}"
		UPPER_RESULT
	)

	set(
		${OUT}
		ENABLE_${UPPER_RESULT}
		PARENT_SCOPE
	)
endfunction()

function(
	sge_check_enable_var
	OUT
	ENABLE_VAR
)
	if(
		NOT ${ENABLE_VAR} STREQUAL "ENABLE_CORE"
		AND NOT ${ENABLE_VAR}
	)
		set(
			${OUT}
			FALSE
			PARENT_SCOPE
		)
	else()
		set(
			${OUT}
			TRUE
			PARENT_SCOPE
		)
	endif()
endfunction()

function(
	check_library_deps
	LIB_NAME
	ADDITONAL_DEPS
)
	foreach(
		DEPENDENCY
		${ADDITONAL_DEPS}
	)
		libname_to_enable_var(
			ENABLE_VAR
			${DEPENDENCY}
		)

		sge_check_enable_var(
			DEP_PRESENT
			${ENABLE_VAR}
		)

		if(
			NOT ${DEP_PRESENT}
		)
			message(
				FATAL_ERROR
				"For ${LIB_NAME} to work you need to -D ${ENABLE_VAR}=ON!"
			)
		endif()
	endforeach()
endfunction()

macro(
	sge_check_optional_deps
	COMPONENT
	SGE_LIBRARIES
)
	foreach(
		SGELIB
		${SGE_LIBRARIES}
	)
		libname_to_enable_var(
			ENABLE_VAR
			${SGELIB}
		)

		sge_check_enable_var(
			DEP_PRESENT
			${ENABLE_VAR}
		)

		if(
			NOT ${DEP_PRESENT}
		)
			message(
				STATUS
				"${COMPONENT} will not be built because ${ENABLE_VAR}=OFF!"
			)

			return()
		endif()
	endforeach()
endmacro()

set(
	SGE_STATIC_LINK_FLAG
	SGE_STATIC_LINK
)

function(
	sge_generate_symbol_header
)
	fcppt_generate_symbol_header(
		STATIC_LINK_FLAG
			"${SGE_STATIC_LINK_FLAG}"
		${ARGN}
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
		EXPORTS_NAME
			"${SYMBOL_NAME}"
		SYMBOL_NAME
			"${SYMBOL_NAME}"
	)
endfunction()

function(
	add_sge_base_library_variant
	SGE_LIB_NAME
	SGE_LIB_FILES
)
	set(
		OPTION_ARGS
		HAS_IMPL_DIR
	)

	set(
		SINGLE_ARGS
		VARIANT
		BASE_VARIANT
	)

	set(
		MULTI_ARGS
		SGE_DEPS
		TRANSITIVE_SGE_DEPS
		ADDITIONAL_DEPS
		ADDITIONAL_DEPS_PKGCONFIG
		TRANSITIVE_ADDITIONAL_DEPS
		TRANSITIVE_ADDITIONAL_DEPS_PKGCONFIG
		INCLUDE_DIRS
		SYSTEM_INCLUDE_DIRS
		TRANSITIVE_INCLUDE_DIRS
		TRANSITIVE_SYSTEM_INCLUDE_DIRS
		COMPILE_DEFINITIONS
		TRANSITIVE_COMPILE_DEFINITIONS
		COMPILE_FLAGS
		USE_IMPL_INCLUDE_OF
		IMPLEMENT_FROM
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
		"${SINGLE_ARGS}"
		"${MULTI_ARGS}"
		${ARGN}
	)

	if(
		NOT
		"${_UNPARSED_ARGUMENTS}"
		STREQUAL
		""
	)
		message(
			FATAL_ERROR
			"Invalid parameters ${_UNPARSED_ARGUMENTS}"
		)
	endif()

	if(
		${_VARIANT}
		STREQUAL
		"STATIC"
	)
		fcppt_utils_static_link_name(
			"${SGE_LIB_NAME}"
			SGE_LIB_NAME
		)
	elseif(
		${_VARIANT}
		STREQUAL
		"INTERFACE"
	)
		fcppt_utils_interface_link_name(
			"${SGE_LIB_NAME}"
			SGE_LIB_NAME
		)
	endif()

	if(
		${_VARIANT}
		STREQUAL
		"INTERFACE"
	)
		add_library(
			${SGE_LIB_NAME}
			${_VARIANT}
		)
	else()
		add_library(
			${SGE_LIB_NAME}
			${_VARIANT}
			${SGE_LIB_FILES}
		)
	endif()

	if(
		NOT
		${_VARIANT}
		STREQUAL
		"INTERFACE"
	)
		set_target_properties(
			${SGE_LIB_NAME}
			PROPERTIES
			VERSION
			${SGE_USED_SO_VERSION}
		)

		fcppt_utils_set_target_compiler_flags(
			${SGE_LIB_NAME}
			ADDITIONAL_FLAGS
			"${_COMPILE_FLAGS}"
		)
	endif()

	fcppt_utils_interface_static_link(
		${SGE_LIB_NAME}
		${_VARIANT}
		${SGE_STATIC_LINK_FLAG}
	)

	transform_sge_link_targets(
		"${_SGE_DEPS}"
		SGE_DEPS_RESULT
	)

	transform_sge_link_targets(
		"${_TRANSITIVE_SGE_DEPS}"
		TRANSITIVE_SGE_DEPS_RESULT
	)

	if(
		NOT
		${_VARIANT}
		STREQUAL
		"INTERFACE"
	)
		set_target_properties(
			${SGE_LIB_NAME}
			PROPERTIES
			FOLDER
			sge
		)

		target_link_libraries(
			${SGE_LIB_NAME}
			PRIVATE
			${_ADDITIONAL_DEPS}
			${SGE_DEPS_RESULT}
		)

		fcppt_utils_link_imported_targets(
			${SGE_LIB_NAME}
			PRIVATE
			${_ADDITIONAL_DEPS_PKGCONFIG}
		)
	endif()

	target_link_libraries(
		${SGE_LIB_NAME}
		INTERFACE
		${TRANSITIVE_SGE_DEPS_RESULT}
		${_TRANSITIVE_ADDITIONAL_DEPS}
	)

	fcppt_utils_link_imported_targets(
		${SGE_LIB_NAME}
		INTERFACE
		${_TRANSITIVE_ADDITIONAL_DEPS_PKGCONFIG}
	)

	# FIXME
	set(
		PUBLIC_INCLUDES
		"$<BUILD_INTERFACE:${FCPPT_UTILS_PROJECT_BINARY_DIR}/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
		${Boost_INCLUDE_DIRS}
	)

	if(
		NOT
		${_VARIANT}
		STREQUAL
		"INTERFACE"
	)
		target_include_directories(
			${SGE_LIB_NAME}
			PRIVATE
			${PUBLIC_INCLUDES}
			${_INCLUDE_DIRS}
		)

		target_include_directories(
			${SGE_LIB_NAME}
			SYSTEM
			PRIVATE
			${_SYSTEM_INCLUDE_DIRS}
		)

		if(
			_HAS_IMPL_DIR
		)
			target_include_directories(
				${SGE_LIB_NAME}
				PRIVATE
				${CMAKE_CURRENT_SOURCE_DIR}/impl/include
			)
		endif()

		# TODO: Get rid of this
		foreach(
			INCLUDE_DEP
			${_USE_IMPL_INCLUDE_OF}
		)
			target_include_directories(
				${SGE_LIB_NAME}
				PRIVATE
				${FCPPT_UTILS_PROJECT_SOURCE_DIR}/libs/${INCLUDE_DEP}/impl/include
			)
		endforeach()

		foreach(
			IMPL_DEP
			${_IMPLEMENT_FROM}
		)
			string(
				TOUPPER
				${IMPL_DEP}
				UPPER_IMPL_DEP
			)

			target_compile_definitions(
				${SGE_LIB_NAME}
				PRIVATE
				"SGE_${UPPER_IMPL_DEP}_DETAIL_INSTANTIATE_EXPORTS"
			)

			target_include_directories(
				${SGE_LIB_NAME}
				PRIVATE
				${FCPPT_UTILS_PROJECT_SOURCE_DIR}/libs/${IMPL_DEP}/impl/include
			)
		endforeach()
	endif()

	target_include_directories(
		${SGE_LIB_NAME}
		INTERFACE
		${PUBLIC_INCLUDES}
		${_TRANSITIVE_INCLUDE_DIRS}
	)

	target_include_directories(
		${SGE_LIB_NAME}
		SYSTEM
		INTERFACE
		${_TRANSITIVE_SYSTEM_INCLUDE_DIRS}
	)

	if(
		NOT
		${_VARIANT}
		STREQUAL
		"INTERFACE"
	)
		target_compile_definitions(
			${SGE_LIB_NAME}
			PRIVATE
			${_COMPILE_DEFINITIONS}
		)
	endif()

	target_compile_definitions(
		${SGE_LIB_NAME}
		INTERFACE
		${_TRANSITIVE_COMPILE_DEFINITIONS}
	)

	#Example libs should not be exported
	if(
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
			"${CMAKE_INSTALL_LIBDIR}"
		)
	endif()
endfunction()

function(
	is_path_prefix_of
	RESULT
	PREFIX_STRING
	PATH_STRING
)
	set(
		${RESULT}
		FALSE
		PARENT_SCOPE
	)

	set(
		CURRENT_DIRECTORY
		"${PATH_STRING}"
	)

	while(
		TRUE
	)
		if(
			"${PREFIX_STRING}"
			STREQUAL "${CURRENT_DIRECTORY}"
		)
			set(
				${RESULT}
				TRUE
				PARENT_SCOPE
			)

			break()
		endif()

		get_filename_component(
			NEW_CURRENT_DIRECTORY
			"${CURRENT_DIRECTORY}"
			PATH
		)

		if(
			"${NEW_CURRENT_DIRECTORY}"
			STREQUAL
			"${CURRENT_DIRECTORY}"
		)
			break()
		endif()

		set(
			CURRENT_DIRECTORY
			"${NEW_CURRENT_DIRECTORY}"
		)
	endwhile()
endfunction()

function(
	add_sge_base_library_base
	RELATIVE_PATH
)
	set(
		OPTION_ARGS
		HAS_IMPL_DIR
	)

	set(
		SINGLE_ARGS
		BASE_VARIANT
	)

	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		ADDITIONAL_DEPS_PKGCONFIG
		TRANSITIVE_SGE_DEPS
		TRANSITIVE_ADDITIONAL_DEPS
		TRANSITIVE_ADDITIONAL_DEPS_PKGCONFIG
		INCLUDE_DIRS
		SYSTEM_INCLUDE_DIRS
		TRANSITIVE_INCLUDE_DIRS
		TRANSITIVE_SYSTEM_INCLUDE_DIRS
		COMPILE_DEFINITIONS
		TRANSITIVE_COMPILE_DEFINITIONS
		COMPILE_FLAGS
		USE_IMPL_INCLUDE_OF
		IMPLEMENT_FROM
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
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

	foreach(
		INCLUDE_DIR
		${_INCLUDE_DIRS}
	)
		is_path_prefix_of(
			INCLUDE_DIR_IS_PREFIX_OF_SOURCE_DIR
			${FCPPT_UTILS_PROJECT_SOURCE_DIR}
			${INCLUDE_DIR}
		)

		is_path_prefix_of(
			INCLUDE_DIR_IS_PREFIX_OF_BINARY_DIR
			${FCPPT_UTILS_PROJECT_BINARY_DIR}
			${INCLUDE_DIR}
		)

		if(
			${INCLUDE_DIR_IS_PREFIX_OF_SOURCE_DIR}
			AND
			NOT
			${INCLUDE_DIR_IS_PREFIX_OF_BINARY_DIR}
		)
			message(
				"${LIB_NAME} includes ${INCLUDE_DIR}, which is part of sge's source directory"
			)
	#	elseif(
	#			${INCLUDE_DIR_IS_PREFIX_OF_BINARY_DIR}
	#	)
	#		message(
	#			"${LIB_NAME} includes ${INCLUDE_DIR}, which is part of sge's binary directory"
	#		)
		endif()
	endforeach()

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
		# TODO: Use fcppt_utils here
		set(
			SGE_DUMMY_SOURCE_FILE
			"${CMAKE_CURRENT_BINARY_DIR}/dummy.cpp"
		)

		configure_file(
			${FCPPT_UTILS_PROJECT_SOURCE_DIR}/cmake/dummy.cpp.in
			${SGE_DUMMY_SOURCE_FILE}
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
			EXPORTS_NAME
				"${SGE_LIB_NAME}"
			SYMBOL_NAME
				"SGE_${SGE_LIB_SYMBOL}_DETAIL"
			RELATIVE_PATH
				"sge/${RELATIVE_PATH}/detail"
		)
	endif()

	add_sge_base_library_variant(
		${SGE_LIB_NAME}
		"${SGE_LIB_FILES}"
		VARIANT
		"INTERFACE"
		${ARGN}
	)

	if(
		ENABLE_SHARED
		AND NOT
		"${_BASE_VARIANT}" STREQUAL "DUMMY"
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
			"${CMAKE_CURRENT_SOURCE_DIR}/include/sge/${RELATIVE_PATH}"
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
			"${CMAKE_INSTALL_INCLUDEDIR}/sge/${DEST_INCLUDE_PATH}"
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
# SYSTEM_INCLUDE_DIRS:
#	Like INCLUDE_DIRS, but treated as system headers.
#
# TRANSITIVE_INCLUDE_DIRS:
#	A list of include directories a consumer of the library needs to be
#	built.
#
# TRANSITIVE_SYSTEM_INCLUDE_DIRS:
#   Like TRANSITIVE_INCLUDE_DIRS, but treated as system headers.
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
#
# HAS_IMPL_DIR:
#	If set to true, include the impl/include directory.
#
# USE_IMPL_INCLUDE_OF:
#	A list of sge libraries to use the impl include directory from.
#
# IMPLEMENT_FROM:
#	A list of sge libraries to implement templates from
#
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
# SYSTEM_INCLUDE_DIRS:
#	As above but included as SYSTEM.
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
		SYSTEM_INCLUDE_DIRS
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
		MODULE
		${SGE_${UPPER_PLUGIN_NAME}_FILES_ABS}
	)

	set_target_properties(
		${SGE_PLUGIN_NAME}
		PROPERTIES
		FOLDER
		sge/plugins
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

	target_include_directories(
		${SGE_PLUGIN_NAME}
		SYSTEM
		PRIVATE
		${_SYSTEM_INCLUDE_DIRS}
	)

	target_compile_definitions(
		${SGE_PLUGIN_NAME}
		PRIVATE
		${_COMPILE_DEFINITIONS}
	)

	set_target_properties(
		${SGE_PLUGIN_NAME}
		PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY
		${SGE_PLUGIN_BUILD_PATH}
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

if(
	MSVC
)
	set(
		SGE_MSVC_BIGOBJ_FLAGS
		"/bigobj"
	)
endif()
