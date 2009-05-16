FILE (GLOB_RECURSE sgevorbisfiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libvorbis/include)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libogg/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libvorbis/lib)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libogg/lib)
ELSE ()
	pkg_check_modules (VORBIS vorbis)
ENDIF ()

ADD_LIBRARY (sgevorbis SHARED ${sgevorbisfiles})

TARGET_LINK_LIBRARIES (sgevorbis sgecore vorbisfile ${VORBIS_LDFLAGS})

IF (MSVC)
	TARGET_LINK_LIBRARIES (sgevorbis ogg vorbis)
ENDIF()

INSTALL (TARGETS sgevorbis DESTINATION ${pluginpath})
