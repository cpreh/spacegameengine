fcppt_utils_load_source_files(libs/console/files.txt SGE_CONSOLE_FILES)

add_sge_base_library(
  console
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgefont
  sgeparse
  TRANSITIVE_SGE_DEPS
  sgecore
  sgefont_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_parse_interface
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_boost_interface)
