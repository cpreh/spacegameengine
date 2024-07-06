fcppt_utils_load_source_files(libs/parseini/files.txt SGE_PARSEINI_FILES)

add_sge_base_library(
  parse/ini
  SGE_DEPS
  sgeparse
  TRANSITIVE_SGE_DEPS
  sgeparse_interface
  USE_IMPL_INCLUDE_OF
  core
  parse
  ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_parse_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_parse_interface)
