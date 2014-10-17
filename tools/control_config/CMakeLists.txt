set(
	SGE_TOOL_CONTROL_CONFIG_FILES
	tools/control_config/include/control_config/test.hpp
	tools/control_config/src/main.cpp
	tools/control_config/src/test.cpp
)

add_sge_tool(
	control_config
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)
