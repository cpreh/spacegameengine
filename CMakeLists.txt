cmake_minimum_required(VERSION 3.27.0)

project(sge)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SGE_CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(SGE_PUBLIC_CMAKE_MODULE_PATH ${SGE_CMAKE_MODULE_PATH}/public)

list(APPEND CMAKE_MODULE_PATH ${SGE_PUBLIC_CMAKE_MODULE_PATH}
     ${SGE_CMAKE_MODULE_PATH}/private)

include(GNUInstallDirs)

find_package(fcppt REQUIRED)

# TODO: Remove default arguments eventually.
list(
  APPEND
  FCPPT_UTILS_CLANG_TIDY_ADDITIONAL_CHECKS
  "-cppcoreguidelines-avoid-const-or-ref-data-members"
  "-fuchsia-default-arguments-calls"
  "-fuchsia-default-arguments-declarations"
  "-fuchsia-virtual-inheritance"
  "-misc-misplaced-const")

set(FCPPT_UTILS_CLANG_TIDY_WHITELIST "fcppt" "awl" "mizuiro" "sge")

include(SGEFunctions)

include(FcpptCMakeUtils)

include(FcpptSymbol)

fcppt_utils_handle_so_version(SGE_SO_VERSION SGE_USED_SO_VERSION "0.1")

fcppt_utils_static_shared()

option(ENABLE_TEST "Build the tests" OFF)

find_package(Boost 1.70.0 CONFIG REQUIRED)

set(MEDIA_INSTALL_DIR "${FCPPT_UTILS_INSTALL_DATA_DIR}/media")

set(SGE_INSTALL_PLUGIN_DIR_BASE
    "${CMAKE_INSTALL_LIBDIR}"
    CACHE STRING "Custom plugin base installation directory")

set(PLUGIN_INSTALL_DIR "${SGE_INSTALL_PLUGIN_DIR_BASE}/${PROJECT_NAME}")

set(OpenGL_GL_PREFERENCE GLVND)

add_subdirectory(libs)

add_subdirectory(plugins)

option(ENABLE_TOOLS "Build all tools" ON)

if(ENABLE_TOOLS)
  add_subdirectory(tools)
endif()

option(ENABLE_DOC "Build the documentation" OFF)

if(ENABLE_DOC)
  add_subdirectory(doc)
endif()

option(ENABLE_EXAMPLES "Build the examples" OFF)

if(ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()

if(ENABLE_TEST)
  find_package(Catch2 REQUIRED)

  fcppt_utils_setup_tests()

  enable_testing()

  add_subdirectory(tests)
endif()

get_property(SGE_LIBRARIES GLOBAL PROPERTY SGE_LIBRARIES_GLOBAL)

fcppt_utils_generate_config(
  CONFIG_PATH ${FCPPT_UTILS_PROJECT_SOURCE_DIR}/cmake MODULES_PATH
  ${FCPPT_UTILS_PROJECT_SOURCE_DIR}/cmake/modules/public)

install(DIRECTORY media/ DESTINATION ${MEDIA_INSTALL_DIR})

install(DIRECTORY ${SGE_PUBLIC_CMAKE_MODULE_PATH}/
        DESTINATION ${FCPPT_UTILS_INSTALL_CMAKEMODULES_DIR})
