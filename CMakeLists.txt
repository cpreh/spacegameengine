PROJECT (spacegameengine)

INCLUDE (CheckCXXSourceCompiles)
INCLUDE (OWGetGCCVersion.cmake)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

SET (CMAKE_REQUIRED_FLAGS "-std=c++0x")

CHECK_CXX_SOURCE_COMPILES(
	"template<typename... Args> void f(Args... args) {} int main(){}"
	SGE_HAVE_VARIADIC_TEMPLATES
)

CHECK_CXX_SOURCE_COMPILES(
	"static_assert(sizeof(char) == 1, \"sizeof char is 1\"); int main(){}"
	SGE_HAVE_STATIC_ASSERT
)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	ow_get_gcc_version (gccversion)

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal")

	IF (${gccversion} STRGREATER "4.3.0" OR ${gccversion} STREQUAL "4.3.0")
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -std=c++0x")
	ENDIF ()
ELSEIF (${MSVC})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4512 /wd4355 /wd4800 /wd4996")
	SET (WINLIBS projects/windows/lib32)
	SET (WININCLUDES ${CMAKE_SOURCE_DIR}/${WINLIBS})

	ADD_DEFINITIONS (-DUNICODE=1 -D_UNICODE=1)
ENDIF ()

INCLUDE_DIRECTORIES (include)

CONFIGURE_FILE(config.h.in include/sge/config.h)

SET (pluginpath ${CMAKE_INSTALL_PREFIX}/lib/sge)
SET (include_dest ${CMAKE_INSTALL_PREFIX}/include/)
SET (media_dest ${CMAKE_INSTALL_PREFIX}/share/games/sge/media/)

IF (ENABLE_DEBUG AND CMAKE_COMPILER_IS_GNUCXX)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb")
ENDIF ()


ADD_SUBDIRECTORY (src)

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

MACRO (INSTALL_HEADERS subpath)
	FILE (GLOB sgeheaders include/${subpath}/*.h*)
	INSTALL (FILES ${sgeheaders} DESTINATION ${include_dest}${subpath})
ENDMACRO ()

INSTALL_HEADERS (sge)
INSTALL_HEADERS (sge/archive)
INSTALL_HEADERS (sge/audio)
INSTALL_HEADERS (sge/audio/loader)
INSTALL_HEADERS (sge/audio/player)
INSTALL_HEADERS (sge/console)
INSTALL_HEADERS (sge/detail)
INSTALL_HEADERS (sge/font)
INSTALL_HEADERS (sge/image)
INSTALL_HEADERS (sge/input)
INSTALL_HEADERS (sge/math)
INSTALL_HEADERS (sge/math/detail)
INSTALL_HEADERS (sge/model)
INSTALL_HEADERS (sge/renderer)
INSTALL_HEADERS (sge/sprite)
INSTALL_HEADERS (sge/texture)
