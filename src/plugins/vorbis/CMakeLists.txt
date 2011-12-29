set(
	SGE_VORBIS_FILES
	src/plugins/vorbis/include/sge/vorbis/file.hpp
	src/plugins/vorbis/include/sge/vorbis/loader.hpp
	src/plugins/vorbis/include/sge/vorbis/stream_ptr.hpp
	src/plugins/vorbis/src/exports.cpp
	src/plugins/vorbis/src/file.cpp
	src/plugins/vorbis/src/loader.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

include_directories(
	${VORBIS_INCLUDE_DIR}
)

include_directories(
	${OGG_INCLUDE_DIR}
)

add_sge_plugin(
	vorbis
	"sgeaudio"
	"${OGG_LIBRARY};${VORBIS_LIBRARY};${VORBIS_FILE_LIBRARY}"
)
