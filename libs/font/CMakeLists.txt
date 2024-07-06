fcppt_utils_load_source_files(libs/font/files.txt SGE_FONT_FILES)

find_package(mizuiro REQUIRED)

add_sge_base_library(
  font
  SGE_DEPS
  sgecore
  sgelog
  sgeplugin
  sgeimage2d_interface
  sgeimagecolor_interface
  TRANSITIVE_SGE_DEPS
  sgecore
  sgeimage2d_interface
  sgeimagecolor_interface
  sgeplugin_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  mizuiro_interface
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  mizuiro_interface
  fcppt_core_interface
  fcppt_log_interface
  IMPLEMENT_FROM
  plugin)
