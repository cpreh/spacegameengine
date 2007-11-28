FILE (GLOB sgevorbisfiles src/*.cpp)

INCLUDE (UsePkgConfig)

ADD_LIBRARY (sgevorbis SHARED ${sgevorbisfiles})

IF(${UNIX})
	PKGCONFIG (vorbis vorbisincludedir vorbislibdir vorbislinkflags vorbiscflags)
ELSEIF (${WIN32})
	INCLUDE_DIRECTORIES (${WINLIBS}/libvorbis/include)
	LINK_DIRECTORIES (${WINLIBS}/libvorbis/lib)
ENDIF ()

TARGET_LINK_LIBRARIES (sgevorbis sgecore vorbisfile ${vorbislinkflags})

INSTALL (TARGETS sgevorbis DESTINATION ${pluginpath})
