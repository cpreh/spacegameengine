FILE (GLOB sgevorbisfiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libvorbis/include)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libogg/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libvorbis/lib)
ENDIF ()

ADD_LIBRARY (sgevorbis SHARED ${sgevorbisfiles})

IF(${UNIX})
	INCLUDE (FindPkgConfig)

	pkg_check_modules (VORBIS vorbis)
ENDIF ()

TARGET_LINK_LIBRARIES (sgevorbis sgecore vorbisfile ${VORBIS_LDFLAGS})

INSTALL (TARGETS sgevorbis DESTINATION ${pluginpath})
