find_package(
	OpenCL
)

include_directories(
	${OPENCL_INCLUDE_DIRS}
)

message("Fix the opencl simple example!")

#add_sge_console_example(
#	opencl_simple
#	"sgelog;sgeopencl;sgerenderer;sgesystems;sgeviewport;sgewindow"
#	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
#)

add_sge_console_example(
	opencl_syntax_checker
	"sgelog;sgeopencl"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_console_example(
	opencl_texture_read
	"sgeconfig;sgeimage2d;sgemedia;sgeopencl;sgesystems"
	"${Fcppt_core_LIBRARIES}"
)

