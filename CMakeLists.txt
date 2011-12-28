cmake_minimum_required(
	VERSION 2.6
)

project(
	spacegameengine
)

set(
	CMAKE_MODULE_PATH
	"${CMAKE_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}"
)

include(
	FcpptCMakeUtils
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

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

find_package(
	Boost 1.47.0 REQUIRED
)

include_directories(
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

# Workaround Boost-1.48 bug, remove this as soon as this is fixed in a boost
# release
if(
	MSVC AND ${Boost_VERSION} STREQUAL "104800"
)
	add_definitions(
		-D BOOST_FUSION_DONT_USE_PREPROCESSED_FILES
	)
endif()


# FIND FCPPT
find_package(
	Fcppt
	REQUIRED
)

add_definitions(
	${Fcppt_DEFINITIONS}
)

include_directories(
	${Fcppt_INCLUDE_DIRS}
)

# FIND MIZUIRO
find_package(
	Mizuiro
	REQUIRED
)

include_directories(
	${Mizuiro_INCLUDE_DIRS}
)

# FIND AWL
find_package(
	Awl
	REQUIRED
)

include_directories(
	${Awl_INCLUDE_DIRS}
)

# TODO: Check if this is needed (or move it to fcppt/awl)
if(MSVC)
	add_definitions(-DUNICODE=1 -D_UNICODE=1)
endif()

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

add_subdirectory(
	src
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

if(
	ENABLE_EXAMPLES
)
	add_subdirectory(
		examples
	)
endif()

option(
	ENABLE_TEST
	"Build the tests"
	OFF
)

if(
	ENABLE_TEST
)
	enable_testing()

	add_subdirectory(
		tests
	)
endif()

install(
	DIRECTORY
	media/
	DESTINATION
	${MEDIA_INSTALL_DIR}
)

install(
	FILES
	${CMAKE_SOURCE_DIR}/CMakeModules/FindSGE.cmake
	${CMAKE_SOURCE_DIR}/CMakeModules/FindCEGUI.cmake
	${CMAKE_SOURCE_DIR}/CMakeModules/SGECustomPath.cmake
	DESTINATION
	${INSTALL_CMAKEMODULES_DIR}
)
