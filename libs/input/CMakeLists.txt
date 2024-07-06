fcppt_utils_load_source_files(libs/input/files.txt SGE_INPUT_FILES)

find_package(awl REQUIRED)

add_sge_base_library(
  input
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgelog
  sgeplugin
  sgewindow
  TRANSITIVE_SGE_DEPS
  sgecore_interface
  sgelog_interface
  sgeplugin_interface
  sgewindow_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_log_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface
  IMPLEMENT_FROM
  plugin)
