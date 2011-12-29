set(
	SGE_FREETYPE_FILES
	src/plugins/freetype/include/sge/freetype/char_metric.hpp
	src/plugins/freetype/include/sge/freetype/face.hpp
	src/plugins/freetype/include/sge/freetype/face_fwd.hpp
	src/plugins/freetype/include/sge/freetype/freetype.hpp
	src/plugins/freetype/include/sge/freetype/glyph.hpp
	src/plugins/freetype/include/sge/freetype/library.hpp
	src/plugins/freetype/include/sge/freetype/library_fwd.hpp
	src/plugins/freetype/include/sge/freetype/metrics.hpp
	src/plugins/freetype/include/sge/freetype/system.hpp
	src/plugins/freetype/src/char_metric.cpp
	src/plugins/freetype/src/exports.cpp
	src/plugins/freetype/src/face.cpp
	src/plugins/freetype/src/glyph.cpp
	src/plugins/freetype/src/library.cpp
	src/plugins/freetype/src/metrics.cpp
	src/plugins/freetype/src/system.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

include_directories(
	${FREETYPE_INCLUDE_DIRS}
)

add_sge_plugin(
	freetype
	"sgecharconv;sgefont;sgeimage2d"
	"${FREETYPE_LIBRARY}"
)
