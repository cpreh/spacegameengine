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

	target_link_libraries(
		"${FULL_NAME}"
		${Awl_LIBRARIES}
	)

	transform_sge_link_targets(
		"${SGE_LIBRARIES}"
	)

	if(
		SGE_DEFAULT_LINK_STATIC
	)
		sge_set_static_flags(
			"${FULL_NAME}"
		)
	endif()

	list(
		APPEND
		INCLUDE_DIRS
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
	)

	sge_add_include_dirs(
		"${FULL_NAME}"
		"${INCLUDE_DIRS}"
	)

	target_link_libraries(
		"${FULL_NAME}"
		"${ADDITIONAL_LIBRARIES}"
		"${SGELIBS_TARGETS_RESULT}"
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
