CHECK_DEPENDENCIES(
	"PARSE"
	"fontbitmap"
)

SET(
	SGE_FONT_BITMAP_FILES
	include/sge/font/bitmap/char_metric.hpp
	include/sge/font/bitmap/char_metric_fwd.hpp
	include/sge/font/bitmap/char_metric_ptr.hpp
	include/sge/font/bitmap/create.hpp
	include/sge/font/bitmap/metrics.hpp
	include/sge/font/bitmap/symbol.hpp
	src/font/bitmap/char_metric.cpp
	src/font/bitmap/create.cpp
	src/font/bitmap/load_offset.cpp
	src/font/bitmap/load_offset.hpp
	src/font/bitmap/load_rect.cpp
	src/font/bitmap/load_rect.hpp
	src/font/bitmap/metrics.cpp
)

ADD_SGE_BASE_LIBRARY(
	font_bitmap
	"sgeparse"
)
