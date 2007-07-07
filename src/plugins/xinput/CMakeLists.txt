FILE (GLOB sgexinputfiles src/*.cpp)

ADD_LIBRARY (sgexinput SHARED ${sgexinputfiles})
TARGET_LINK_LIBRARIES (sgexinput sgecore X11 Xxf86dga)

IF (DEFINED {ENABLE_DGA})
	ADD_DEFINITIONS (-DENABLE_DGA=1)
ENDIF ()

INSTALL (TARGETS sgexinput DESTINATION ${pluginpath})
