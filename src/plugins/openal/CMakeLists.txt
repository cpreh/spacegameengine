FILE (GLOB sgeopenalfiles src/*.cpp)

INCLUDE_DIRECTORIES(${OPENAL_INCLUDE_DIR})

ADD_LIBRARY (sgeopenal SHARED ${sgeopenalfiles})

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgeopenal sgecore openal)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgeopenal sgecore openal32)
ENDIF ()

INSTALL (TARGETS sgeopenal DESTINATION ${pluginpath})
