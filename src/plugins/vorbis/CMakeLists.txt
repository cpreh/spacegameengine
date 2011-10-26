SET(
	SGE_VORBIS_FILES
	src/plugins/vorbis/include/sge/vorbis/file.hpp
	src/plugins/vorbis/include/sge/vorbis/loader.hpp
	src/plugins/vorbis/include/sge/vorbis/stream_ptr.hpp
	src/plugins/vorbis/src/exports.cpp
	src/plugins/vorbis/src/file.cpp
	src/plugins/vorbis/src/loader.cpp
)

INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

INCLUDE_DIRECTORIES(
	${VORBIS_INCLUDE_DIR}
)

INCLUDE_DIRECTORIES(
	${OGG_INCLUDE_DIR}
)

ADD_SGE_PLUGIN(
	vorbis
	"sgeaudio;${OGG_LIBRARY};${VORBIS_LIBRARY};${VORBIS_FILE_LIBRARY}"
)
