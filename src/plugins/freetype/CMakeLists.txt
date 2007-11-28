FILE (GLOB sgefreetypefiles src/*.cpp)

ADD_LIBRARY (sgefreetype SHARED ${sgefreetypefiles})
TARGET_LINK_LIBRARIES (sgefreetype sgecore freetype)

IF (${WIN32})
	INCLUDE_DIRECTORIES (sgefreetype ${WINLIBS}/freetype/include ${WINLIBS}/freetype/include/freetype2)
ELSE ()
	INCLUDE_DIRECTORIES (sgefreetype /usr/include/freetype2)
ENDIF ()

INSTALL (TARGETS sgefreetype DESTINATION ${pluginpath})
