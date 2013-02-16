cmake_minimum_required(
	VERSION 2.6
)

project(
	sge
)

set(
	CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}"
)

include(
	FcpptCMakeUtils
)

fcppt_utils_prepare_config()

include(
	FcpptSymbol
)

fcppt_utils_handle_so_version(
	SGE_SO_VERSION
	SGE_USED_SO_VERSION
	"0.1"
)

include(
	SGEFunctions
)

# Put libraries and exe files in the same directory
# because Windows lacks 'rpath'
if(
	MSVC
)
	set(
		LIBRARY_OUTPUT_PATH
		${EXECUTABLE_OUTPUT_PATH}
	)
endif()

option(
	ENABLE_SHARED
	"Build sge as shared libraries"
	TRUE
)

option(
	ENABLE_STATIC
	"Build sge as as static libraries"
	FALSE
)

if(
	NOT ENABLE_SHARED AND NOT ENABLE_STATIC
)
	message(
		FATAL_ERROR
		"You disabled both STATIC and SHARED"
	)
endif()

if(
	ENABLE_STATIC
	AND NOT ENABLE_SHARED
)
	set(
		SGE_DEFAULT_LINK_STATIC
		TRUE
	)
endif()

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

option(
	ENABLE_TEST
	"Build the tests"
	OFF
)

set(
	NEEDED_BOOST_LIBS
	"chrono;filesystem;program_options;system"
)

if(
	ENABLE_TEST
)
	list(
		APPEND
		NEEDED_BOOST_LIBS
		"unit_test_framework"
	)
endif()

find_package(
	Boost 1.47.0 REQUIRED COMPONENTS
	"${NEEDED_BOOST_LIBS}"
)

include_directories(
	${FCPPT_UTILS_INCLUDE_SYSTEM}
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)


# FIND FCPPT
find_package(
	fcppt
	REQUIRED
)

add_definitions(
	${fcppt_DEFINITIONS}
)

include_directories(
	${fcppt_INCLUDE_DIRS}
)

# FIND MIZUIRO
find_package(
	mizuiro
	REQUIRED
)

include_directories(
	${mizuiro_INCLUDE_DIRS}
)

# FIND AWL
find_package(
	awl
	REQUIRED
)

include_directories(
	${awl_INCLUDE_DIRS}
)

set(
	MEDIA_INSTALL_DIR
	"${INSTALL_DATA_DIR}/media"
)

set(
	INSTALL_PLUGIN_DIR_BASE
	"${INSTALL_LIBRARY_DIR}"
	CACHE
	STRING
	"Custom plugin base installation directory"
)

set(
	PLUGIN_INSTALL_DIR
	"${INSTALL_PLUGIN_DIR_BASE}/${CMAKE_PROJECT_NAME}"
)

include_directories(
	"${CMAKE_BINARY_DIR}/include"
)

add_subdirectory(
	src
)

add_subdirectory(
	tools
)

option(
	ENABLE_DOC
	"Build the documentation"
	OFF
)

if(
	ENABLE_DOC
)
	add_subdirectory(
		doc
	)
endif()

option(
	ENABLE_EXAMPLES
	"Build the examples"
	OFF
)

macro(
	sge_check_optional_deps
	COMPONENT
	SGE_LIBRARIES
)
	foreach(
		SGELIB
		${SGE_LIBRARIES}
	)
		string(
			REPLACE
			"sge"
			""
			SGELIB_SUFFIX
			${SGELIB}
		)

		string(
			TOUPPER
			${SGELIB_SUFFIX}
			SGELIB_UPPER
		)

		if(
			NOT ${SGELIB_UPPER} STREQUAL "CORE"
			AND NOT ENABLE_${SGELIB_UPPER}
		)
			message(
				STATUS
				"${COMPONENT} will not be built because ${SGELIB} is not enabled!"
			)

			return()
		endif()
	endforeach()
endmacro()

if(
	ENABLE_EXAMPLES
)
	add_subdirectory(
		examples
	)
endif()

if(
	ENABLE_TEST
)
	enable_testing()

	add_subdirectory(
		tests
	)
endif()

get_property(
	SGE_LIBRARIES
	GLOBAL
	PROPERTY
	SGE_LIBRARIES_GLOBAL
)

fcppt_utils_generate_config()

install(
	DIRECTORY
	media/
	DESTINATION
	${MEDIA_INSTALL_DIR}
)

install(
	FILES
	${CMAKE_SOURCE_DIR}/CMakeModules/FindCg.cmake
	${CMAKE_SOURCE_DIR}/CMakeModules/FindCEGUI.cmake
	${CMAKE_SOURCE_DIR}/CMakeModules/SGECustomPath.cmake
	DESTINATION
	${INSTALL_CMAKEMODULES_DIR}
)
