CHECK_DEPENDENCIES(
	"PARSE"
	"bitmapfont"
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

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_FONT_BITMAP_FILES}"
	SGE_FONT_BITMAP_FILES_ABS
)

ADD_LIBRARY(
	sgefontbitmap
	SHARED
	${SGE_FONT_BITMAP_FILES_ABS}
)

TARGET_LINK_LIBRARIES(
	sgefontbitmap
	sgecore
	sgeparse
)

INSTALL(
	TARGETS
	sgefontbitmap
	DESTINATION
	lib
)

INSTALL(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/include/sge/font/bitmap
	DESTINATION
	include/sge
)
