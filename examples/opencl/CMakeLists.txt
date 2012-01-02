#find_package(
#	OpenCL
#	REQUIRED
#)

#include_directories(
#	${OPENCL_INCLUDE_DIRS}
#)

add_sge_example(
	openclsimple
	"sgelog;sgeopencl;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES}"
)

add_sge_example(
	openclsyntax_checker
	"sgelog;sgeopencl"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	opencltexture_read
	"sgeconfig;sgeimage2d;sgemedia;sgeopencl;sgesystems"
	"${Fcppt_core_LIBRARIES}"
)
