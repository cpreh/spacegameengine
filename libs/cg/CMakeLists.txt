fcppt_utils_load_source_files(libs/cg/files.txt SGE_CG_FILES)

add_sge_base_library(
  cg
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${Cg_LIBRARIES}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  SYSTEM_INCLUDE_DIRS
  ${Cg_INCLUDE_DIRS}
  TRANSITIVE_SYSTEM_INCLUDE_DIRS
  ${Cg_INCLUDE_DIRS})
