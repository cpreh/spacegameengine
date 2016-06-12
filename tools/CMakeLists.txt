find_package(
	awl
	REQUIRED
)

include(
	AwlMainGenerator
)

include(
	CMakeParseArguments
)

function(
	add_sge_tool
	TOOL_NAME
)
	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		INCLUDE_DIRS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	check_library_deps(
		"${TOOL_NAME}"
		"${SGE_LIBRARIES}"
	)

	string(
		TOUPPER
		"${TOOL_NAME}"
		UPPER_TOOL_NAME
	)

	set(
		FULL_NAME
		"sge_tool_${TOOL_NAME}"
	)

	set(
		SOURCE_FILE
		"${EXAMPLE_NAME}.cpp"
	)

	fcppt_utils_append_source_dir_and_make_groups(
		"${SGE_TOOL_${UPPER_TOOL_NAME}_FILES}"
		SGE_TOOL_${UPPER_TOOL_NAME}_FILES_ABS
	)

	awl_utils_add_portable_executable(
		"${FULL_NAME}"
		"tool_main"
		"${SGE_TOOL_${UPPER_TOOL_NAME}_FILES_ABS}"
	)

	fcppt_utils_set_target_compiler_flags(
		${FULL_NAME}
	)

	transform_sge_link_targets(
		"${_SGE_DEPS}"
		SGE_LIBRARIES_RESULT
	)

	target_include_directories(
		"${FULL_NAME}"
		PRIVATE
		"${FCPPT_UTILS_PROJECT_SOURCE_DIR}/tools/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		${_INCLUDE_DIRS}
	)

	target_link_libraries(
		"${FULL_NAME}"
		PRIVATE
		${awl_TARGET}
		${_ADDITIONAL_DEPS}
		${SGE_LIBRARIES_RESULT}
	)

	install(
		TARGETS
		"${FULL_NAME}"
		DESTINATION
		"${INSTALL_BINARY_DIR}"
	)
endfunction()

option(
	ENABLE_CONTROL_CONFIG
	"Build the control config tool"
	ON
)

if(
	ENABLE_CONTROL_CONFIG
)
	add_subdirectory(
		control_config
	)
endif()
