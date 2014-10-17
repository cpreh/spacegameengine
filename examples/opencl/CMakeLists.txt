add_sge_console_example(
	opencl_simple
	"sgelog;sgeopencl;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${fcppt_log_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	opencl_syntax_checker
	"sgelog;sgeopencl"
	"${fcppt_core_TARGET};${fcppt_log_TARGET};${fcppt_filesystem_TARGET}"
	""
)

add_sge_console_example(
	opencl_texture_read
	"sgeconfig;sgeimage2d;sgemedia;sgeopencl;sgesystems"
	"${fcppt_core_TARGET}"
	""
)
