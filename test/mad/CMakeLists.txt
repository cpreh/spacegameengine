CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT (HELLO)

INCLUDE (CheckCXXSourceRuns)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

CHECK_CXX_SOURCE_RUNS(
	"#include <sge/config.h>
	 #include <cstdlib>
	 int main() {
	 #ifdef SGE_HAVE_VARIADIC_TEMPLATES
	 	return 0;
	 #else
	 	return EXIT_FAILURE;
	 #endif
	 }"
	 HAVE_VARIADIC_TEMPLATES)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal -Winit-self -O3")
ENDIF ()

IF (ENABLE_DEBUG AND CMAKE_COMPILER_IS_GNUCXX)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF ()

IF (HAVE_VARIADIC_TEMPLATES)
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ENDIF ()

FILE (GLOB files *.cpp)

ADD_EXECUTABLE(main ${files})
TARGET_LINK_LIBRARIES(main sgecore mad boost_program_options)
