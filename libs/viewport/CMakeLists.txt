fcppt_utils_load_source_files(libs/viewport/files.txt SGE_VIEWPORT_FILES)

find_package(awl REQUIRED)

add_sge_base_library(
  viewport
  HAS_IMPL_DIR
  SGE_DEPS
  sgerenderer
  sgewindow
  TRANSITIVE_SGE_DEPS
  sgerenderer_interface
  sgewindow_interface
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  awl_interface
  fcppt_core_interface)
