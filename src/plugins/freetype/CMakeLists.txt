SET(
	SGE_FREETYPE_FILES
	src/plugins/freetype/char_metric.hpp
	src/plugins/freetype/face.hpp
	src/plugins/freetype/face_fwd.hpp
	src/plugins/freetype/freetype.hpp
	src/plugins/freetype/glyph.hpp
	src/plugins/freetype/library.hpp
	src/plugins/freetype/library_fwd.hpp
	src/plugins/freetype/metrics.hpp
	src/plugins/freetype/src/char_metric.cpp
	src/plugins/freetype/src/exports.cpp
	src/plugins/freetype/src/face.cpp
	src/plugins/freetype/src/glyph.cpp
	src/plugins/freetype/src/library.cpp
	src/plugins/freetype/src/metrics.cpp
	src/plugins/freetype/src/system.cpp
	src/plugins/freetype/system.hpp
)

INCLUDE_DIRECTORIES(
	${FREETYPE_INCLUDE_DIRS}
)

ADD_SGE_PLUGIN(
	freetype
	"${FREETYPE_LIBRARY}"
)
