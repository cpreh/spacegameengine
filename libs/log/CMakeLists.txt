fcppt_utils_load_source_files(libs/log/files.txt SGE_LOG_FILES)

add_sge_base_library(
  log
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface)
