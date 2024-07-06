fcppt_utils_load_source_files(libs/media/files.txt SGE_MEDIA_FILES)

sge_generate_instantiate_symbol_header(media)

add_sge_base_library(
  media
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgelog
  sgeplugin_interface
  TRANSITIVE_SGE_DEPS
  sgelog_interface
  sgeplugin_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET})
