FILE (GLOB sgeopenalfiles src/*.cpp)

ADD_LIBRARY (sgeopenal SHARED ${sgeopenalfiles})

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgeopenal sgecore openal)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgeopenal sgecore openal32)
ENDIF ()

INSTALL (TARGETS sgeopenal DESTINATION ${pluginpath})
