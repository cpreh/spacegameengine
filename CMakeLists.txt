CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT (spacegameengine)

INCLUDE (CheckIncludeFile)
INCLUDE (CheckCXXCompilerFlag)
INCLUDE (CheckCXXSourceCompiles)
INCLUDE (CheckCXXSourceRuns)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

CHECK_CXX_COMPILER_FLAG(
	"-std=c++0x"
	SGE_HAVE_VARIADIC_TEMPLATES
)

CHECK_CXX_SOURCE_COMPILES(
	"#include <boost/cstdint.hpp>
	 int main()
	 {
	   boost::uint_least64_t test;
	 }"
	 SGE_HAVE_ATLEAST_UINT64)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	CHECK_CXX_COMPILER_FLAG(
		"-fvisibility=hidden"
		SGE_HAVE_GCC_VISIBILITY)

	ADD_DEFINITIONS ("-ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self -Woverloaded-virtual")

	IF (${SGE_HAVE_GCC_VISIBILITY})
		ADD_DEFINITIONS("-fvisibility=hidden")
	ENDIF ()

	IF (${SGE_HAVE_VARIADIC_TEMPLATES})
		ADD_DEFINITIONS ("-Wold-style-cast -std=c++0x")
	ENDIF ()
ELSEIF (${MSVC})
	ADD_DEFINITIONS ("/W4 /wd4512 /wd4355 /wd4800 /wd4996 /wd4714")
	SET (WINLIBS projects/windows/lib32)
	SET (WININCLUDES ${CMAKE_SOURCE_DIR}/${WINLIBS})

	ADD_DEFINITIONS (-DUNICODE=1 -D_UNICODE=1)
ENDIF ()

INCLUDE_DIRECTORIES (include)

CONFIGURE_FILE(config.h.in include/sge/config.h)

SET (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

IF (WIN32)
	SET (pluginpath ${CMAKE_BINARY_DIR}/plugins)
	SET (media_dest ${CMAKE_SOURCE_DIR}/media)
ELSE ()
	SET (pluginpath ${CMAKE_INSTALL_PREFIX}/lib/sge)
	SET (include_dest ${CMAKE_INSTALL_PREFIX}/include/)
	SET (media_dest ${CMAKE_INSTALL_PREFIX}/share/games/sge/media/)
ENDIF ()

MACRO (INSTALL_HEADERS subpath)
	FILE (GLOB sgeheaders include/${subpath}/*.h*)
	INSTALL (FILES ${sgeheaders} DESTINATION ${include_dest}${subpath})
ENDMACRO ()

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

INSTALL_HEADERS (sge)
INSTALL_HEADERS (sge/algorithm)
INSTALL_HEADERS (sge/algorithm/detail)
INSTALL_HEADERS (sge/archive)
INSTALL_HEADERS (sge/audio)
INSTALL_HEADERS (sge/audio/loader)
INSTALL_HEADERS (sge/audio/player)
INSTALL_HEADERS (sge/console)
INSTALL_HEADERS (sge/detail)
INSTALL_HEADERS (sge/font)
INSTALL_HEADERS (sge/image)
INSTALL_HEADERS (sge/input)
INSTALL_HEADERS (sge/log)
INSTALL_HEADERS (sge/log/format)
INSTALL_HEADERS (sge/math)
INSTALL_HEADERS (sge/math/detail)
INSTALL_HEADERS (sge/model)
INSTALL_HEADERS (sge/mpl)
INSTALL_HEADERS (sge/plugin)
INSTALL_HEADERS (sge/random)
INSTALL_HEADERS (sge/renderer)
INSTALL_HEADERS (sge/renderer/glsl)
INSTALL_HEADERS (sge/renderer/state)
INSTALL_HEADERS (sge/renderer/vf)
INSTALL_HEADERS (sge/signals)
INSTALL_HEADERS (sge/sprite)
INSTALL_HEADERS (sge/systems)
INSTALL_HEADERS (sge/texture)
INSTALL_HEADERS (sge/time)
