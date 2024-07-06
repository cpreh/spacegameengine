fcppt_utils_load_source_files(libs/rucksackviewport/files.txt SGE_RUCKSACKVIEWPORT_FILES)

add_sge_base_library(
  "rucksack/viewport"
  SGE_DEPS
  sgerenderer
  sgerucksack
  sgeviewport
  TRANSITIVE_SGE_DEPS
  sgerenderer_interface
  sgerucksack_interface
  sgeviewport_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
