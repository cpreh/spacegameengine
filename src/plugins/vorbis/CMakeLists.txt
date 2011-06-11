SET(
	SGE_VORBIS_FILES
	src/plugins/vorbis/container_source.hpp
	src/plugins/vorbis/file.hpp
	src/plugins/vorbis/loader.hpp
	src/plugins/vorbis/src/exports.cpp
	src/plugins/vorbis/src/file.cpp
	src/plugins/vorbis/src/loader.cpp
	src/plugins/vorbis/stream_ptr.hpp
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
