cmake_minimum_required(
	VERSION
	2.8.12
)

project(
	sge
)

set(
	CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}"
)

include(
	FcpptCMakeUtils
)

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

fcppt_utils_static_shared()

option(
	ENABLE_TEST
	"Build the tests"
	OFF
)

set(
	NEEDED_BOOST_LIBS
	"filesystem;program_options;system"
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

link_directories(
	${Boost_LIBRARY_DIRS}
)

find_package(
	fcppt
	REQUIRED
)

fcppt_utils_install_data_dir(
	INSTALL_DATA_DIR
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
	"${INSTALL_PLUGIN_DIR_BASE}/${PROJECT_NAME}"
)

add_subdirectory(
	src
)

option(
	ENABLE_TOOLS
	"Build all tools"
	ON
)

if(
	ENABLE_TOOLS
)
	add_subdirectory(
		tools
	)
endif()

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

set(
	sge_BVH_INCLUDE_DIRS
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/include
)

set(
	sge_PROJECTILE_INCLUDE_DIRS
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/include
)

set(
	sge_TIMER_INCLUDE_DIRS
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/include
)

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

fcppt_utils_generate_config(
	TRUE
)

install(
	DIRECTORY
	media/
	DESTINATION
	${MEDIA_INSTALL_DIR}
)

install(
	FILES
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/CMakeModules/FindCg.cmake
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/CMakeModules/FindCEGUI.cmake
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/CMakeModules/SGECustomPath.cmake
	DESTINATION
	${INSTALL_CMAKEMODULES_DIR}
)
