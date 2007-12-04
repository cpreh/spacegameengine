FILE (GLOB sgezlibfiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/zlib/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/zlib/lib)
ENDIF ()

ADD_LIBRARY (sgezlib SHARED ${sgezlibfiles})
TARGET_LINK_LIBRARIES (sgezlib sgecore miniunzip)

INSTALL (TARGETS sgezlib DESTINATION ${pluginpath})
