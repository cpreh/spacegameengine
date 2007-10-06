PROJECT (spacegameengine)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic -Wall -Wextra -Wconversion -Wfloat-equal")
ELSEIF (${MSVC})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4512 /wd4355 /wd4800")
ENDIF ()


SET (pluginpath ${CMAKE_INSTALL_PREFIX}/lib/sge)
SET (include_dest ${CMAKE_INSTALL_PREFIX}/include/sge/)
SET (media_dest ${CMAKE_INSTALL_PREFIX}/share/games/sge/media/)

IF (ENABLE_DEBUG AND CMAKE_COMPILER_IS_GNUCXX)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -g3 -ggdb")
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
