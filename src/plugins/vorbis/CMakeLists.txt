FILE (GLOB_RECURSE sgevorbisfiles src/*.cpp)

INCLUDE_DIRECTORIES(${VORBIS_INCLUDE_DIR})

ADD_LIBRARY (sgevorbis SHARED ${sgevorbisfiles})

TARGET_LINK_LIBRARIES (
	sgevorbis
	sgecore
	${VORBIS_FILE_LIBRARY}
)

INSTALL (TARGETS sgevorbis DESTINATION lib/sge)
