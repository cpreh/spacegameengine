fcppt_utils_load_source_files(libs/audio/files.txt SGE_AUDIO_FILES)

add_sge_base_library(
  audio
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgelog
  sgemedia
  sgeplugin
  TRANSITIVE_SGE_DEPS
  sgecore
  sgemedia_interface
  sgeplugin_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  fcppt_core_interface
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface
  IMPLEMENT_FROM
  media
  plugin)
