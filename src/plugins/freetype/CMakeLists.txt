FILE (GLOB sgefreetypefiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/freetype/include ${WININCLUDES}/freetype/include/freetype2)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/freetype/lib)
ELSE ()
	pkg_check_modules(FREETYPE2 freetype2)
	INCLUDE_DIRECTORIES(${FREETYPE2_INCLUDE_DIRS})
ENDIF ()

ADD_LIBRARY (sgefreetype SHARED ${sgefreetypefiles})
TARGET_LINK_LIBRARIES (sgefreetype sgecore freetype)

INSTALL (TARGETS sgefreetype DESTINATION ${pluginpath})
