fcppt_utils_load_source_files(libs/parsejson/files.txt SGE_PARSEJSON_FILES)

add_sge_base_library(
  parse/json
  HAS_IMPL_DIR
  SGE_DEPS
  sgecharconv
  sgeparse
  TRANSITIVE_SGE_DEPS
  sgecharconv
  sgeparse
  USE_IMPL_INCLUDE_OF
  core
  parse
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_boost_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_boost_interface)
