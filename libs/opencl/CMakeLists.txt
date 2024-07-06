fcppt_utils_load_source_files(libs/opencl/files.txt SGE_OPENCL_FILES)

find_package(OpenGL)

if(WIN32)
  set(SGE_OPENCL_HAVE_WINDOWS TRUE)
else()
  find_file(GLX_HEADER glx.h PATHS "${OPENGL_INCLUDE_DIR}/GL")

  if(GLX_HEADER)
    set(SGE_OPENCL_HAVE_GLX TRUE)

    set(SGE_OPENCL_ADDITIONAL_DEPS OpenGL::GLX)
  endif()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/sge/opencl/config.hpp)

set(OPENCL_TARGET "CL_TARGET_OPENCL_VERSION=110")

add_sge_base_library(
  opencl
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgeimagecolor
  sgeimage2d
  sgelog
  sgerenderer
  sgerendereropengl
  TRANSITIVE_SGE_DEPS
  sgecore_interface
  sgeimagecolor_interface
  sgeimage2d_interface
  sgerenderer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  fcppt_parse_interface
  ${OpenCL_LIBRARIES}
  OpenGL::GL
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface
  INCLUDE_DIRS
  ${OpenCL_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  "${CMAKE_CURRENT_BINARY_DIR}/include"
  COMPILE_DEFINITIONS
  "CL_USE_DEPRECATED_OPENCL_1_1_APIS"
  ${OPENCL_TARGET}
  TRANSITIVE_COMPILE_DEFINITIONS
  ${OPENCL_TARGET})
