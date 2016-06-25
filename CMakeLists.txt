cmake_minimum_required(
	VERSION
	2.8.12
)

project(
	sge
)

set(
	SGE_CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
)

set(
	SGE_PUBLIC_CMAKE_MODULE_PATH
	${SGE_CMAKE_MODULE_PATH}/public
)

list(
	APPEND
	CMAKE_MODULE_PATH
	${SGE_PUBLIC_CMAKE_MODULE_PATH}
	${SGE_CMAKE_MODULE_PATH}/private
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
	libs
)

add_subdirectory(
	plugins
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
	CONFIG_PATH
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/cmake
)

install(
	DIRECTORY
	media/
	DESTINATION
	${MEDIA_INSTALL_DIR}
)

install(
	DIRECTORY
	${SGE_PUBLIC_CMAKE_MODULE_PATH}/
	DESTINATION
	${INSTALL_CMAKEMODULES_DIR}
)
