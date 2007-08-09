PROJECT (spacegameengine)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic -Wall -Wextra -Wconversion")
SET (pluginpath /usr/lib/sge)
SET (include_dest /usr/include/sge/)
SET (media_dest /usr/share/games/sge/media/)

IF (${ENABLE_DEBUG})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF ()

ADD_SUBDIRECTORY (src)
ADD_SUBDIRECTORY (3rdparty)

IF (${ENABLE_TEST})
	ADD_SUBDIRECTORY (test)
ENDIF ()

MACRO (INSTALL_MEDIA subpath)
	FILE (GLOB sgemedia media/${subpath}/*?.*)
	INSTALL (FILES ${sgemedia} DESTINATION ${media_dest}${subpath})
ENDMACRO ()

INSTALL_MEDIA (./)
INSTALL_MEDIA (fonts)
INSTALL_MEDIA (mainskin)
