fcppt_utils_load_source_files(libs/rucksack/files.txt SGE_RUCKSACK_FILES)

add_sge_base_library(
  "rucksack"
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
