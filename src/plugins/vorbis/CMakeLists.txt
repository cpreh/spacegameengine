set(
	SGE_VORBIS_FILES
	src/plugins/vorbis/include/sge/vorbis/file.hpp
	src/plugins/vorbis/include/sge/vorbis/loader.hpp
	src/plugins/vorbis/include/sge/vorbis/stream_ptr.hpp
	src/plugins/vorbis/src/exports.cpp
	src/plugins/vorbis/src/file.cpp
	src/plugins/vorbis/src/loader.cpp
)

add_sge_plugin(
	vorbis
	"sgeaudio;sgelog;sgeplugin"
	"${Fcppt_filesystem_LIBRARIES};${OGG_LIBRARY};${VORBIS_LIBRARY};${VORBIS_FILE_LIBRARY}"
	"${VORBIS_INCLUDE_DIR};${OGG_INCLUDE_DIR}"
)
