PROJECT (spacegameengine)

INCLUDE (CheckCXXSourceCompiles)
INCLUDE (CheckCXXSourceRuns)

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

SET (CMAKE_REQUIRED_FLAGS "")

CHECK_CXX_SOURCE_COMPILES(
	"#include <X11/Xlib.h>
	 int main(){}"
	 SGE_HAVE_X11
)

IF (${SGE_HAVE_X11})
	CHECK_CXX_SOURCE_COMPILES(
		"#include <X11/Xlib.h>
		 #include <X11/extensions/xf86vmode.h>
		 int main() {}"
		SGE_HAVE_XF86_VIDMODE
	)
	CHECK_CXX_SOURCE_COMPILES(
		"#include <X11/Xlib.h>
		 #include <X11/extensions/xf86dga.h>
		 int main() {}"
		SGE_HAVE_XF86_DGA
	)
ENDIF ()

CHECK_CXX_SOURCE_RUNS(
	"#include <unistd.h>
	 #include <cstdlib>
	 int main()
	 {
	   return _POSIX_VERSION >= 200100
	          ? EXIT_SUCCESS
		  : EXIT_FAILURE;
	 }"
	 SGE_HAVE_POSIX)

FIND_PACKAGE(Boost 1.35.0 COMPONENTS
	filesystem
	signals
	regex
	iostreams
	system)

CHECK_CXX_SOURCE_COMPILES(
	"#include <boost/cstdint.hpp>
	 int main()
	 {
	   boost::uint_least64_t test;
	 }"
	 SGE_HAVE_ATLEAST_UINT64)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_REQUIRED_FLAGS "-fvisibility=hidden")

	CHECK_CXX_SOURCE_COMPILES(
		"int main(){}"
		SGE_HAVE_GCC_VISIBILITY)

	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self")

	IF (${SGE_HAVE_GCC_VISIBILITY})
		SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
	ENDIF ()

	IF (${SGE_HAVE_VARIADIC_TEMPLATES})
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
INSTALL_HEADERS (sge/plugin)
INSTALL_HEADERS (sge/renderer)
INSTALL_HEADERS (sge/renderer/glsl)
INSTALL_HEADERS (sge/sprite)
INSTALL_HEADERS (sge/texture)
INSTALL_HEADERS (sge/time)
