SET(
	SGE_FONTBITMAP_FILES
	include/sge/font/bitmap/bitmap.hpp
	include/sge/font/bitmap/create.hpp
	include/sge/font/bitmap/symbol.hpp
	src/font/bitmap/char_metric.cpp
	src/font/bitmap/create.cpp
	src/font/bitmap/include/sge/src/font/bitmap/char_map.hpp
	src/font/bitmap/include/sge/src/font/bitmap/char_metric.hpp
	src/font/bitmap/include/sge/src/font/bitmap/load_offset.hpp
	src/font/bitmap/include/sge/src/font/bitmap/load_one_file.hpp
	src/font/bitmap/include/sge/src/font/bitmap/load_rect.hpp
	src/font/bitmap/include/sge/src/font/bitmap/metrics.hpp
	src/font/bitmap/load_offset.cpp
	src/font/bitmap/load_one_file.cpp
	src/font/bitmap/load_rect.cpp
	src/font/bitmap/metrics.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

ADD_SGE_BASE_LIBRARY(
	fontbitmap
	"sgefont;sgeimage2d;sgeparse"
	""
)
