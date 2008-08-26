FILE (GLOB sgex11inputfiles src/*.cpp)

ADD_LIBRARY (sgex11input SHARED ${sgex11inputfiles})
TARGET_LINK_LIBRARIES (sgex11input sgecore X11)

IF (${ENABLE_DGA})
	ADD_DEFINITIONS (-DENABLE_DGA=1)
	TARGET_LINK_LIBRARIES (sgex11input Xxf86dga)
ENDIF ()

INSTALL (TARGETS sgex11input DESTINATION ${pluginpath})
