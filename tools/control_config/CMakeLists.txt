set(
	SGE_TOOL_CONTROL_CONFIG_FILES
	tools/control_config/src/main.cpp
)

add_sge_tool(
	control_scheme
	"sgeconfig;sgefont;sgefontdraw;sgeimage;sgeinput;sgeparse;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)
