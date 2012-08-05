set(
	SGE_FONTDRAW_FILES
	include/sge/font/draw/detail/static_text_impl_fwd.hpp
	include/sge/font/draw/simple.hpp
	include/sge/font/draw/static_text.hpp
	include/sge/font/draw/static_text_fwd.hpp
	src/font/draw/detail/static_text_impl.cpp
	src/font/draw/include/sge/src/font/draw/detail/static_text_impl.hpp
	src/font/draw/simple.cpp
	src/font/draw/static_text.cpp
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_sge_base_library(
	"font/draw"
	"sgecore;sgefont;sgeimage;sgeimage2d;sgerenderer;sgesprite;sgetexture"
	""
	""
	""
)
