find_package(
	awl
	REQUIRED
)

include(
	AwlMainGenerator
)

function(
	add_sge_tool
	TOOL_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
	INCLUDE_DIRS
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

	target_link_libraries(
		"${FULL_NAME}"
		${awl_TARGET}
	)

	transform_sge_link_targets(
		"${SGE_LIBRARIES}"
		SGE_LIBRARIES_RESULT
	)

	list(
		APPEND
		INCLUDE_DIRS
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
	)

	target_include_directories(
		"${FULL_NAME}"
		PRIVATE
		${INCLUDE_DIRS}
	)

	target_link_libraries(
		"${FULL_NAME}"
		${ADDITIONAL_LIBRARIES}
		${SGE_LIBRARIES_RESULT}
	)

	install(
		TARGETS
		"${FULL_NAME}"
		DESTINATION
		"${INSTALL_BINARY_DIR}"
	)
endfunction()

include_directories(
	include
)

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
