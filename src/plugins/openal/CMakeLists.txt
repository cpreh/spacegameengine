FILE (GLOB sgeopenalfiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES(${WININCLUDES}/openal/include)
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/${WINLIBS}/openal/lib)
ELSE ()
	INCLUDE_DIRECTORIES(${OPENAL_INCLUDE_DIR})
ENDIF ()

ADD_LIBRARY (sgeopenal SHARED ${sgeopenalfiles})

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgeopenal sgecore openal)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgeopenal sgecore OpenAL32)
ENDIF ()

INSTALL (TARGETS sgeopenal DESTINATION ${pluginpath})
