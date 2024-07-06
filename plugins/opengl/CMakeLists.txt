fcppt_utils_load_source_files(plugins/opengl/files.txt SGE_OPENGL_BASE_FILES)

set(SGE_OPENGL_FILES "${SGE_OPENGL_BASE_FILES}")

set(SGE_OPENGL_INCLUDE_DIRS "")

function(add_opengl_backend_files backend)
  fcppt_utils_load_source_files(plugins/opengl/backends/${backend}/files.txt backend_files)

  list(APPEND SGE_OPENGL_FILES ${backend_files})
  set(SGE_OPENGL_FILES ${SGE_OPENGL_FILES} PARENT_SCOPE)

  list(APPEND SGE_OPENGL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/backends/${backend}/include)
  set(SGE_OPENGL_INCLUDE_DIRS ${SGE_OPENGL_INCLUDE_DIRS} PARENT_SCOPE)
endfunction()

include(FindPkgConfig)

find_package(awl REQUIRED)

pkg_check_modules(EGL IMPORTED_TARGET egl)

option(ENABLE_OPENGL_EGL "Use EGL in OpenGL" OFF)

set(SGE_OPENGL_SYSTEM_INCLUDE_DIRS "")

set(SGE_OPENGL_SGE_DEPS
    sgeimagecolor
    sgeimageds
    sgeimageds2d
    sgeimage2d
    sgeimage3d
    sgelog
    sgeplugin
    sgerenderer
    sgerendereropengl
    sgewindow)

set(SGE_OPENGL_ADDITIONAL_DEPS ${OPENGL_gl_LIBRARY} ${awl_TARGET}
                               ${fcppt_log_TARGET})

pkg_check_modules(X11_OPENGL IMPORTED_TARGET x11 xrandr)

option(ENABLE_OPENGL_X11 "Enable X11 backend in OpenGL" ${X11_OPENGL_FOUND})

option(ENABLE_OPENGL_GLX "Enable GLX backend in OpenGL" ${ENABLE_OPENGL_X11})

if(ENABLE_OPENGL_X11)
  set(SGE_OPENGL_HAVE_X11 TRUE)

  add_opengl_backend_files(x11)

  # TODO: Make this optional
  add_opengl_backend_files(xrandr)

  list(APPEND SGE_OPENGL_ADDITIONAL_DEPS PkgConfig::X11_OPENGL)

  if(ENABLE_OPENGL_EGL)
    add_opengl_backend_files(egl_x11)
  endif()

  if(ENABLE_OPENGL_GLX)
    set(SGE_OPENGL_HAVE_GLX TRUE)

    list(APPEND SGE_OPENGL_ADDITIONAL_DEPS OpenGL::GLX)

    add_opengl_backend_files(glx)
  endif()
endif()

if(ENABLE_OPENGL_WAYLAND AND ENABLE_OPENGL_EGL)
  pkg_check_modules(WAYLAND_EGL REQUIRED IMPORTED_TARGET wayland-egl)

  set(SGE_OPENGL_HAVE_WAYLAND TRUE)

  add_opengl_backend_files(wayland)

  list(APPEND SGE_OPENGL_ADDITIONAL_DEPS PkgConfig::WAYLAND_EGL)
endif()

if(WIN32)
  add_opengl_backend_files(windows)
endif()

if(ENABLE_CG)
  add_opengl_backend_files(cg)

  list(APPEND SGE_OPENGL_INCLUDE_DIRS ${Cg_INCLUDE_DIRS})

  list(APPEND SGE_OPENGL_ADDITIONAL_DEPS ${Cg_LIBRARIES} ${Cg_GL_LIBRARIES})

  list(APPEND SGE_OPENGL_SGE_DEPS sgecg sgerenderercg)
endif()

if(ENABLE_OPENGL_EGL)
  set(SGE_OPENGL_HAVE_EGL TRUE)

  add_opengl_backend_files(egl)

  list(APPEND SGE_OPENGL_ADDITIONAL_DEPS PkgConfig::EGL)
endif()

option(ENABLE_OPENGL_SDL "Enable SDL backend in OpenGL" ${ENABLE_SDL})

if(ENABLE_OPENGL_SDL)
  find_package(SDL2 REQUIRED)

  set(SGE_OPENGL_HAVE_SDL TRUE)

  add_opengl_backend_files(sdl)

  list(APPEND SGE_OPENGL_SYSTEM_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})

  list(APPEND SGE_OPENGL_ADDITIONAL_DEPS ${SDL2_LIBRARIES})
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/sge/opengl/config.hpp)

list(APPEND SGE_OPENGL_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/include"
     "${OPENGL_INCLUDE_DIR}")

include(CheckCXXSourceCompiles)

set(CMAKE_REQUIRED_INCLUDES ${SGE_OPENGL_INCLUDE_DIRS})

check_cxx_source_compiles(
  "
	#include <GL/gl.h>
	#include <GL/glext.h>
	int main() { return 0; }"
  HAVE_GLEXT)

unset(CMAKE_REQUIRED_INCLUDES)

if(NOT HAVE_GLEXT)
  message(STATUS "glext.h not found, going to include our own")

  list(APPEND SGE_OPENGL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ext/include)
endif()

if(WIN32)
  list(APPEND SGE_OPENGL_INCLUDE_DIRS
       ${CMAKE_CURRENT_SOURCE_DIR}/wglext/include)
endif()

add_sge_plugin(
  opengl
  SGE_DEPS
  ${SGE_OPENGL_SGE_DEPS}
  ADDITIONAL_DEPS
  ${SGE_OPENGL_ADDITIONAL_DEPS}
  fcppt_boost_interface
  INCLUDE_DIRS
  ${SGE_OPENGL_INCLUDE_DIRS}
  SYSTEM_INCLUDE_DIRS
  ${SGE_OPENGL_SYSTEM_INCLUDE_DIRS}
  COMPILE_DEFINITIONS
  ${SGE_OPENGL_DEFINITIONS})
