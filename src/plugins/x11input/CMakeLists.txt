FILE (GLOB sgex11inputfiles src/*.cpp)

CHECK_CXX_SOURCE_COMPILES("
	#include <X11/Xlib.h>
	#include <X11/extensions/xf86dga.h>
	int main() {}"
	HAVE_XF86_DGA_H
)

IF (HAVE_XF86_DGA_H)
	FIND_LIBRARY(
		HAVE_XF86_DGA
		"Xxf86dga")
ENDIF()

ADD_LIBRARY (sgex11input SHARED ${sgex11inputfiles})
TARGET_LINK_LIBRARIES (sgex11input sgecore X11)

IF (ENABLE_DGA AND HAVE_XF86_DGA)
	ADD_DEFINITIONS (-DSGE_USE_DGA)
	TARGET_LINK_LIBRARIES (sgex11input Xxf86dga)
ENDIF()

INSTALL (TARGETS sgex11input DESTINATION ${pluginpath})
