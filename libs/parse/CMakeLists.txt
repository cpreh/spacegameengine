fcppt_utils_load_source_files(libs/parse/files.txt SGE_PARSE_FILES)

sge_generate_instantiate_symbol_header(parse)

add_sge_base_library(
  parse
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_parse_interface
  ${fcppt_filesystem_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_parse_interface
  ${fcppt_filesystem_TARGET})
