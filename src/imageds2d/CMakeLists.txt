set(
	SGE_IMAGEDS2D_FILES
	include/sge/imageds2d/d16.hpp
	include/sge/imageds2d/d16_format.hpp
	include/sge/imageds2d/d16_fwd.hpp
	include/sge/imageds2d/d24s8.hpp
	include/sge/imageds2d/d24s8_format.hpp
	include/sge/imageds2d/d24s8_fwd.hpp
	include/sge/imageds2d/d32.hpp
	include/sge/imageds2d/d32_format.hpp
	include/sge/imageds2d/d32_fwd.hpp
	src/imageds2d/d16.cpp
	src/imageds2d/d24s8.cpp
	src/imageds2d/d32.cpp
)

sge_implement_from_lib(
	image
)

add_sge_base_library(
	imageds2d
	"sgeimage;sgeimageds"
	""
	""
	""
	"${CMAKE_BINARY_DIR}/src/image/include;${CMAKE_CURRENT_SOURCE_DIR}/include"
)
