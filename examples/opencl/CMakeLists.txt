find_package(
	OpenCL
	REQUIRED
)

include_directories(
	${OPENCL_INCLUDE_DIRS}
)

add_sge_example(openclsimple "sgesystems;sgeviewport;sgerenderer;sgeopencl" "${OPENCL_LIBRARIES}")
add_sge_example(opencltexture_read "sgesystems;sgeimage2d;sgeopencl;sgeconfig" "${OPENCL_LIBRARIES}")
add_sge_example(openclsyntax_checker "sgeopencl" "${OPENCL_LIBRARIES}")
