FILE (GLOB sgex11inputfiles src/*.cpp)

IF(${UNIX})
	CHECK_INCLUDE_FILE(
		X11/extensions/xf86dga.h
		SGE_HAVE_XF86_DGA
	)
ENDIF ()

IF (${ENABLE_DGA})
	ADD_DEFINITIONS (-DSGE_USE_DGA)
ENDIF ()

ADD_LIBRARY (sgex11input SHARED ${sgex11inputfiles})
TARGET_LINK_LIBRARIES (sgex11input sgecore X11)

IF (${ENABLE_DGA})
	TARGET_LINK_LIBRARIES (sgex11input Xxf86dga)
ENDIF ()

INSTALL (TARGETS sgex11input DESTINATION ${pluginpath})
