fcppt_utils_load_source_files(libs/resource_tree/files.txt SGE_RESOURCE_TREE_FILES)

add_sge_base_library(
  resource_tree
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore
  ADDITIONAL_DEPS
  ${fcppt_filesystem_TARGET}
  fcppt_core_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  ${fcppt_filesystem_TARGET}
  fcppt_core_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
