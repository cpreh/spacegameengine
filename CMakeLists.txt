CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

SET (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

PROJECT (spacegameengine)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	MESSAGE(
		FATAL_ERROR
		"In-source builds are not permitted. "
		"Make a separate folder for building:\n"
		"mkdir build; cd build; cmake ..\n"
		"Before that, remove the files that cmake"
		"just created:\nrm -rf CMakeCache.txt CMakeFiles"
	)
ENDIF()

INCLUDE (CheckCXXCompilerFlag)

INCLUDE (FindPkgConfig)

IF (CMAKE_COMPILER_IS_GNUCXX)
	CHECK_CXX_COMPILER_FLAG(
		"-fvisibility=hidden"
		SGE_HAVE_GCC_VISIBILITY
	)

	OPTION (
		ENABLE_DEBUG_WARNINGS "Enable -Wpadded and -Weffc++" OFF
	)

	ADD_DEFINITIONS (
		"-ansi -pedantic-errors -Wall -Wextra -Wconversion"
		"-Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self"
		"-Woverloaded-virtual -Wnon-virtual-dtor"
		"-Wsign-promo -Wstrict-aliasing=1 -Wmissing-declarations"
		"-Wold-style-cast"
	)

	IF(ENABLE_DEBUG_WARNINGS)
		SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}" -Wpadded -Weffc++")
	ENDIF()

	SET (CMAKE_CXX_FLAGS_RELEASE "-O3 -fomit-frame-pointer -DNDEBUG")
	
	IF (SGE_HAVE_GCC_VISIBILITY)
		ADD_DEFINITIONS(-fvisibility=hidden)
	ENDIF ()

	# C++ 98 has no long long but boost insists on using it anyway
	ADD_DEFINITIONS ("-Wno-long-long")
ELSEIF (MSVC)
	ADD_DEFINITIONS ("/W4 /wd4996 /EHa /D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
	#4996 - unsafe standard C++ functions

	ADD_DEFINITIONS (-DUNICODE=1 -D_UNICODE=1)
ENDIF ()

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/include)

SET (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Create package file for relocateable package
SET (PKGFILE "${CMAKE_BINARY_DIR}/spacegameengine.pc")
FILE(
	WRITE ${PKGFILE}
	"prefix=${CMAKE_INSTALL_PREFIX}\n"
	"exec_prefix=\${prefix}\n"
	"libdir=\${prefix}/lib\n"
	"includedir=\${prefix}/include\n"
	"\n"
	"Name: Spacegameengine\n"
	"Description: A portable, easy to use engine written in C++\n"
	"Version: 0.1\n"
	"Requires:\n"
	"Libs: -L\${libdir} -lsgecore\n"
)

INSTALL (FILES ${PKGFILE} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)

# FIND BOOST
SET (Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0")

IF(MSVC)
	SET(Boost_USE_STATIC_LIBS ON)
ENDIF()

FIND_PACKAGE(
	Boost 1.43.0 REQUIRED
)

INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# FIND FCPPT
FIND_PACKAGE(Fcppt REQUIRED)

INCLUDE_DIRECTORIES(${FCPPT_INCLUDE_DIRS})

LINK_DIRECTORIES(${FCPPT_LIBRARY_DIRS})

# FIND MIZUIRO
FIND_PACKAGE(Mizuiro REQUIRED)

INCLUDE_DIRECTORIES(${MIZUIRO_INCLUDE_DIRS})

# FIND X11
IF(UNIX)
	FIND_PACKAGE(X11 REQUIRED)

	SET(SGE_HAVE_X11 true)
ENDIF()

CONFIGURE_FILE(
	${CMAKE_SOURCE_DIR}/config.hpp.in
	${CMAKE_SOURCE_DIR}/include/sge/config.hpp
)

MACRO(
	ADD_SGE_SOURCE_GROUP
	GROUPPREFIX
	SOURCEPATH
	PATTERN
	SOURCEVARIABLE
)
	IF("${SOURCEPATH}" STREQUAL "")
		SET(RELATIVEPATH ${PATTERN})
	ELSE()
		SET(RELATIVEPATH ${SOURCEPATH}/${PATTERN})
	ENDIF()
		
	FILE(GLOB GROUPFILES ${RELATIVEPATH})

	STRING(REPLACE "/" "\\" GROUPFOLDER "${SOURCEPATH}")

	SOURCE_GROUP(${GROUPPREFIX}"\\"${GROUPFOLDER} FILES ${GROUPFILES})

	SET(${SOURCEVARIABLE} ${GROUPFILES})
ENDMACRO()

ADD_SUBDIRECTORY (src)

OPTION(ENABLE_TEST "Build the tests" OFF)

IF (ENABLE_TEST)
	ENABLE_TESTING()
	ADD_SUBDIRECTORY (tests)
ENDIF ()

OPTION(ENABLE_EXAMPLES "Build the examples" OFF)

IF (ENABLE_EXAMPLES)
	ADD_SUBDIRECTORY (examples)
ENDIF ()

INSTALL (
	DIRECTORY media/
	DESTINATION share/games/sge/media
)

INSTALL (
	DIRECTORY include/
	DESTINATION include
	REGEX ".*gui.*|.*xcb.*" EXCLUDE
)
