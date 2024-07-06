fcppt_utils_load_source_files(libs/renderer/files.txt SGE_RENDERER_FILES)

find_package(mizuiro REQUIRED)

find_package(awl REQUIRED)

set(SGE_RENDERER_HAVE_CG ${ENABLE_CG})

if(SGE_RENDERER_HAVE_CG)
  set(SGE_RENDERER_CG_DEPS sgecg_interface sgerenderercg_interface)

  # FIXME
  set(ENABLE_RENDERERCG ON)
endif()

add_sge_base_library(
  renderer
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgeimage2d
  sgeimage3d
  sgeimagecolor
  sgeimageds
  sgeimageds2d
  sgelog
  sgeplugin
  sgewindow_interface
  ${SGE_RENDERER_CG_DEPS}
  TRANSITIVE_SGE_DEPS
  sgecore
  sgeimage_interface
  sgeimage2d_interface
  sgeimage3d_interface
  sgeimagecolor_interface
  sgeimageds_interface
  sgeimageds2d_interface
  sgelog_interface
  sgeplugin_interface
  sgewindow_interface
  ${SGE_RENDERER_CG_DEPS}
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_log_TARGET}
  ${awl_TARGET}
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  awl_interface
  mizuiro_interface
  fcppt_core_interface
  fcppt_log_interface
  IMPLEMENT_FROM
  plugin)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
  ${FCPPT_UTILS_PROJECT_BINARY_DIR}/include/sge/renderer/config.hpp)
