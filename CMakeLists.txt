CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
SET (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)


PROJECT (spacegameengine)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
ENDIF()

INCLUDE (CheckIncludeFile)
INCLUDE (CheckCXXCompilerFlag)
INCLUDE (CheckCXXSourceCompiles)
INCLUDE (CheckCXXSourceRuns)
INCLUDE (FindPkgConfig)

SET (CMAKE_VERBOSE_MAKEFILE ON)

IF (MSVC)
	OPTION (ENABLE_NARROW_STRING "Build sge with std::string instead of std::wstring" OFF)
ELSE ()
	OPTION (ENABLE_NARROW_STRING "Build sge with std::string instead of std::wstring" ON)
ENDIF ()

IF (ENABLE_NARROW_STRING)
       SET (SGE_NARROW_STRING true)
ENDIF()

IF (CMAKE_COMPILER_IS_GNUCXX)
	#CHECK_CXX_COMPILER_FLAG(
	#	"-std=c++0x"
	#	SGE_HAVE_VARIADIC_TEMPLATES
	#)

	CHECK_CXX_COMPILER_FLAG(
		"-fvisibility=hidden"
		SGE_HAVE_GCC_VISIBILITY)

	OPTION (ENABLE_DEBUG_WARNINGS "Enable -Wpadded and -Weffc++" OFF)

	ADD_DEFINITIONS ("-pedantic-errors -Wall -Wextra -Wconversion"
	"-Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self"
	"-Woverloaded-virtual -Wnon-virtual-dtor -Wctor-dtor-privacy"
	"-Wsign-promo -Wstrict-aliasing=1 -Wmissing-declarations"
	"-Wold-style-cast")

	IF(ENABLE_DEBUG_WARNINGS)
		ADD_DEFINITIONS("-Wpadded -Weffc++")
	ENDIF()

	ADD_DEFINITIONS(-D BOOST_FILESYSTEM_NO_DEPRECATED)

	SET (CMAKE_CXX_FLAGS_RELEASE "-O3 -fomit-frame-pointer -DNDEBUG")
	SET (CMAKE_CXX_FLAGS_DEBUG "-g")

# -fvisibility=hidden causes problems without inlining, so just switch it on
# in release mode
	IF (SGE_HAVE_GCC_VISIBILITY)
		ADD_DEFINITIONS(-fvisibility=hidden)
		#SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
	ENDIF ()

	#IF (SGE_HAVE_VARIADIC_TEMPLATES)
	#	ADD_DEFINITIONS ("-std=c++0x")
	#ELSE ()
		# C++ 98 has no long long but boost insists on using it anyway
		ADD_DEFINITIONS ("-Wno-long-long -ansi")
	#ENDIF ()

	SET (CMAKE_REQUIRED_FLAGS "-Wall -Werror")

	CHECK_CXX_SOURCE_COMPILES(
		"#pragma message \"test\"
		 int main() {}"
		SGE_HAVE_PRAGMA_MESSAGE)
	
	SET (CMAKE_REQUIRED_FLAGS "")
ELSEIF (MSVC)
	ADD_DEFINITIONS ("/W4 /wd4512 /wd4355 /wd4800 /wd4996 /wd4714")
	SET (WINLIBS projects/windows/lib32)
	SET (WININCLUDES ${CMAKE_SOURCE_DIR}/${WINLIBS})

	SET (SGE_HAVE_PRAGMA_MESSAGE 1)

	ADD_DEFINITIONS (-DUNICODE=1 -D_UNICODE=1)
ENDIF ()

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/include)


SET (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

IF (DONT_INSTALL)
	SET (pluginpath ${CMAKE_BINARY_DIR}/plugins)
	SET (media_dest ${CMAKE_SOURCE_DIR}/media)
ELSE ()
	SET (pluginpath ${CMAKE_INSTALL_PREFIX}/lib/sge)
	SET (include_dest ${CMAKE_INSTALL_PREFIX}/include/)
	SET (media_dest ${CMAKE_INSTALL_PREFIX}/share/games/sge/media/)
ENDIF ()

IF (NOT DONT_INSTALL)
	SET (pkgfile "${CMAKE_BINARY_DIR}/spacegameengine.pc")
	FILE(WRITE ${pkgfile}
		"prefix=${CMAKE_INSTALL_PREFIX}\n"
		"exec_preifx=\${prefix}\n"
		"libdir=\${prefix}/lib\n"
		"includedir=\${prefix}/include\n"
		"\n"
		"Name: Spacegameengine\n"
		"Description: A portable, easy to use engine written in C++\n"
		"Version: 0.1\n"
		"Requires:\n"
		"Libs: -L\${libdir} -lsgecore\n"
		"Cflags: -I\${includedir}/sge")
	#IF(SGE_HAVE_VARIADIC_TEMPLATES)
	#	FILE(APPEND ${pkgfile} " -std=c++0x")
	#ENDIF()
	INSTALL (FILES ${pkgfile} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
ENDIF()

MACRO (INSTALL_HEADERS subpath)
	FILE (GLOB sgeheaders include/${subpath}/*.h*)
	INSTALL (FILES ${sgeheaders} DESTINATION ${include_dest}${subpath})
ENDMACRO ()

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

CHECK_CXX_SOURCE_RUNS(
	"#include <unistd.h>
	 #include <cstdlib>
	int main()
	{
		return _POSIX_TIMERS > 0
			? EXIT_SUCCESS
			: EXIT_FAILURE;
	}"
	SGE_HAVE_CLOCK_GETTIME)

CHECK_CXX_SOURCE_COMPILES(
	"struct test {
	   test(test const &) = delete;
	   test &operator=(test const &) = default;
	 };
	 int main()
	 {}"
	 SGE_HAVE_DEFAULTED_AND_DELETED_FUNCTIONS)

FIND_PACKAGE(Boost 1.35.0 COMPONENTS
	filesystem
	program_options
	system)

IF(NOT Boost_FOUND)
	MESSAGE(STATUS "Boost not found!")
ENDIF()

IF(Boost_INCLUDE_DIR)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ELSE()
	MESSAGE(STATUS "Boost headers not found. You will have to specify them in your build environment or you can use -DBOOST_ROOT= or -DBoost_INCLUDE_DIR to tell cmake where your boost installation is.")
ENDIF()

IF(Boost_LIBRARY_DIRS)
	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ELSE()
	MESSAGE(STATUS "Boost libraries not found. Please set -DBoost_LIBRARY_DIR manually.")
ENDIF()

CHECK_CXX_SOURCE_COMPILES(
	"#include <boost/cstdint.hpp>
	 int main()
	 {
	   boost::uint_least64_t test;
	 }"
	 SGE_HAVE_ATLEAST_UINT64)

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

IF (SGE_HAVE_POSIX)
	find_package(X11 REQUIRED)

#TODO: dga should not be searched here
# but we need it in sgecore as a workaround
	IF(ENABLE_DGA)
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
	ENDIF()

	IF (X11_FOUND)
		set(SGE_HAVE_X11 true)
	ENDIF()
ENDIF()

ADD_SUBDIRECTORY (src)

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/include/sge/config.h)

OPTION(ENABLE_TEST "Build the tests" OFF)

IF (ENABLE_TEST)
	ADD_SUBDIRECTORY (test)
ENDIF ()

MACRO (INSTALL_MEDIA subpath)
	FILE (GLOB sgemedia media/${subpath}/*?.*)
	INSTALL (FILES ${sgemedia} DESTINATION ${media_dest}${subpath})
ENDMACRO ()

INSTALL_MEDIA (./)
INSTALL_MEDIA (fonts)
INSTALL_MEDIA (gui)

INSTALL_HEADERS (sge)
INSTALL_HEADERS (sge/algorithm)
INSTALL_HEADERS (sge/algorithm/detail)
INSTALL_HEADERS (sge/archive)
INSTALL_HEADERS (sge/audio)
INSTALL_HEADERS (sge/audio/loader)
INSTALL_HEADERS (sge/audio/player)
INSTALL_HEADERS (sge/assign)
INSTALL_HEADERS (sge/assign/detail)
INSTALL_HEADERS (sge/console)
INSTALL_HEADERS (sge/console/detail)
INSTALL_HEADERS (sge/collision)
INSTALL_HEADERS (sge/collision/objects)
INSTALL_HEADERS (sge/container)
INSTALL_HEADERS (sge/detail)
INSTALL_HEADERS (sge/endianness)
INSTALL_HEADERS (sge/filesystem)
INSTALL_HEADERS (sge/filesystem/detail)
INSTALL_HEADERS (sge/font)
INSTALL_HEADERS (sge/image)
INSTALL_HEADERS (sge/input)
INSTALL_HEADERS (sge/input/modifier)
INSTALL_HEADERS (sge/io)
INSTALL_HEADERS (sge/io/detail)
INSTALL_HEADERS (sge/library)
INSTALL_HEADERS (sge/log)
INSTALL_HEADERS (sge/log/format)
INSTALL_HEADERS (sge/mainloop)
INSTALL_HEADERS (sge/math)
INSTALL_HEADERS (sge/math/detail)
INSTALL_HEADERS (sge/math/dim)
INSTALL_HEADERS (sge/math/matrix)
INSTALL_HEADERS (sge/math/matrix/detail)
INSTALL_HEADERS (sge/math/vector)
INSTALL_HEADERS (sge/model)
INSTALL_HEADERS (sge/mpl)
INSTALL_HEADERS (sge/parse)
INSTALL_HEADERS (sge/parse/ini)
INSTALL_HEADERS (sge/parse/ini/detail)
INSTALL_HEADERS (sge/plugin)
INSTALL_HEADERS (sge/random)
INSTALL_HEADERS (sge/renderer)
INSTALL_HEADERS (sge/renderer/filter)
INSTALL_HEADERS (sge/renderer/index)
INSTALL_HEADERS (sge/renderer/index/detail)
INSTALL_HEADERS (sge/renderer/glsl)
INSTALL_HEADERS (sge/renderer/glsl/attribute)
INSTALL_HEADERS (sge/renderer/glsl/uniform)
INSTALL_HEADERS (sge/renderer/state)
INSTALL_HEADERS (sge/renderer/vf)
INSTALL_HEADERS (sge/signal)
INSTALL_HEADERS (sge/signal/detail)
INSTALL_HEADERS (sge/sprite)
INSTALL_HEADERS (sge/systems)
INSTALL_HEADERS (sge/texture)
INSTALL_HEADERS (sge/texture/detail)
INSTALL_HEADERS (sge/time)
INSTALL_HEADERS (sge/type_traits)
INSTALL_HEADERS (sge/window)

IF(ENABLE_GUI)
	INSTALL_HEADERS (sge/gui)
	INSTALL_HEADERS (sge/gui/canvas)
	INSTALL_HEADERS (sge/gui/detail)
	INSTALL_HEADERS (sge/gui/detail/managers)
	INSTALL_HEADERS (sge/gui/events)
	INSTALL_HEADERS (sge/gui/layouts)
	INSTALL_HEADERS (sge/gui/skins)
	INSTALL_HEADERS (sge/gui/timer)
	INSTALL_HEADERS (sge/gui/widgets)
	INSTALL_HEADERS (sge/gui/widgets/buttons)
ENDIF()
