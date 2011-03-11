CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

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

SET(EXTRA_CMAKE_MODULE_PATH "" CACHE PATH "Extra paths to search for cmake modules")

SET (CMAKE_MODULE_PATH "${EXTRA_CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/CMakeModules")

INCLUDE (CheckCXXCompilerFlag)
INCLUDE (CheckCXXSourceRuns)
INCLUDE (CheckSymbolExists)

INCLUDE (FindPkgConfig)

CHECK_CXX_SOURCE_RUNS(
	"#include <cstdlib>
	int main()
	{
	#ifdef __clang__
		return EXIT_SUCCESS;
	#else
		return EXIT_FAILURE;
	#endif
	}
	"
	COMPILER_IS_CLANGPP
)

IF (CMAKE_COMPILER_IS_GNUCXX OR COMPILER_IS_CLANGPP)
	CHECK_CXX_COMPILER_FLAG(
		"-fvisibility=hidden"
		SGE_HAVE_GCC_VISIBILITY
	)

	OPTION (
		ENABLE_DEBUG_WARNINGS "Enable -Wpadded and -Weffc++" OFF
	)

	ADD_DEFINITIONS (
		"-ansi -pedantic-errors -Wall -Wextra -Wconversion"
		"-Wfloat-equal -Wredundant-decls -Winit-self"
		"-Woverloaded-virtual -Wnon-virtual-dtor -Wshadow"
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

SET (BINARY_PATH ${CMAKE_BINARY_DIR}/bin)
SET (LIBRARY_OUTPUT_PATH ${BINARY_PATH})
SET (EXECUTABLE_OUTPUT_PATH ${BINARY_PATH})

# FIND BOOST
SET (Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0" "1.46" "1.46.0")

FIND_PACKAGE(
	Boost 1.46.0 REQUIRED
	filesystem
	system
)

INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# FIND FCPPT
FIND_PACKAGE(Fcppt REQUIRED)

INCLUDE_DIRECTORIES(${FCPPT_INCLUDE_DIRS})

# FIND MIZUIRO
FIND_PACKAGE(Mizuiro REQUIRED)

INCLUDE_DIRECTORIES(${MIZUIRO_INCLUDE_DIRS})

SET(CMAKE_REQUIRED_INCLUDES "${CMAKE_REQUIRED_INCLUDES};${MIZUIRO_INCLUDE_DIRS}")

CHECK_SYMBOL_EXISTS(
	"MIZUIRO_HAVE_FCPPT"
	"mizuiro/config.hpp"
	MIZUIRO_HAVE_FCPPT
)

UNSET(CMAKE_REQUIRED_INCLUDES)

IF(NOT MIZUIRO_HAVE_FCPPT)
	MESSAGE(WARNING "mizuiro has not been compiled with -D ENABLE_FCPPT=ON. Ternany visitation will not work.")
ENDIF()

# FIND AWL
FIND_PACKAGE(AWL REQUIRED)

INCLUDE_DIRECTORIES(${AWL_INCLUDE_DIRS})

MACRO(
	APPEND_SOURCE_DIR_AND_MAKE_GROUPS
	FILES
	RESULT
)
	UNSET(
		TEMP_RESULT
	)

	FOREACH(
		CUR_FILE
		${FILES}
	)
		SET(
			WHOLE_FILE
			${CMAKE_SOURCE_DIR}/${CUR_FILE}
		)

		GET_FILENAME_COMPONENT(
			REL_PATH
			${CUR_FILE}
			PATH
		)

		STRING(REPLACE "/" "\\" GROUPFOLDER ${REL_PATH})

		SOURCE_GROUP(
			${GROUPFOLDER}
			FILES
			${WHOLE_FILE}
		)

		SET(
			TEMP_RESULT
			${TEMP_RESULT}
			${WHOLE_FILE}
		)
	ENDFOREACH()

	SET(
		${RESULT}
		"${${RESULT}};${TEMP_RESULT}"
	)
ENDMACRO()

FUNCTION(
	CHECK_DEPENDENCIES
	DEPENDENCIES
	DEPENDEE
)
	FOREACH(
		DEPENDENCY
		${DEPENDENCIES}
	)
		IF(NOT ENABLE_${DEPENDENCY})
			MESSAGE(
				FATAL_ERROR
				"For ${DEPENDEE} to work you need to -D ENABLE_${DEPENDENCY}=ON!"
			)

			RETURN()
		ENDIF()
	
	ENDFOREACH()
ENDFUNCTION()

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

INSTALL(
	DIRECTORY media/
	DESTINATION share/games/sge/media
)

INSTALL(
	FILES
	${CMAKE_SOURCE_DIR}/FindSGE.cmake
	DESTINATION share/cmake/Modules
)
