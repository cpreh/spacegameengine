FILE (GLOB sgefreetypefiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/freetype/include ${WININCLUDES}/freetype/include/freetype2)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/freetype/lib)
ENDIF ()

ADD_LIBRARY (sgefreetype SHARED ${sgefreetypefiles})
TARGET_LINK_LIBRARIES (sgefreetype sgecore freetype)

IF (${UNIX})
	INCLUDE_DIRECTORIES (sgefreetype /usr/include/freetype2)
ENDIF ()

INSTALL (TARGETS sgefreetype DESTINATION ${pluginpath})
