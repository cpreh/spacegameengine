FILE (GLOB sgezlibfiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/zlib/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/zlib/lib)
ENDIF ()

ADD_LIBRARY (sgezlib SHARED ${sgezlibfiles})

TARGET_LINK_LIBRARIES (sgezlib sgecore)
IF (MSVC)
	TARGET_LINK_LIBRARIES (sgezlib zlibwapi.lib)
ELSE ()
	TARGET_LINK_LIBRARIES (sgezlib miniunzip)
ENDIF ()



INSTALL (TARGETS sgezlib DESTINATION ${pluginpath})
