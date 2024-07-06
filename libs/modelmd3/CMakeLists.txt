fcppt_utils_load_source_files(libs/modelmd3/files.txt SGE_MODELMD3_FILES)

add_sge_base_library(
  "model/md3"
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgelog
  TRANSITIVE_SGE_DEPS
  sgecore
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface)
