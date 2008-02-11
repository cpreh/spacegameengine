FILE (GLOB sgexinputfiles src/*.cpp)

ADD_LIBRARY (sgexinput SHARED ${sgexinputfiles})
TARGET_LINK_LIBRARIES (sgexinput sgecore X11)

IF (${ENABLE_DGA})
	ADD_DEFINITIONS (-DENABLE_DGA=1)
	TARGET_LINK_LIBRARIES (sgexinput Xxf86dga)
ENDIF ()

INSTALL (TARGETS sgexinput DESTINATION ${pluginpath})
