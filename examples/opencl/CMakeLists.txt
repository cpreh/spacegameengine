find_package(
	OpenCL
	REQUIRED
)

add_sge_console_example(
	opencl_simple
	"sgelog;sgeopencl;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${OPENCL_INCLUDE_DIRS}"
)

add_sge_console_example(
	opencl_syntax_checker
	"sgelog;sgeopencl"
	"${fcppt_core_TARGET};${fcppt_filesystem_TARGET}"
	"${OPENCL_INCLUDE_DIRS}"
)

add_sge_console_example(
	opencl_texture_read
	"sgeconfig;sgeimage2d;sgemedia;sgeopencl;sgesystems"
	"${fcppt_core_TARGET}"
	"${OPENCL_INCLUDE_DIRS}"
)
