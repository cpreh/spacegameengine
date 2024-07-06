fcppt_utils_load_source_files(libs/core/files.txt SGE_CORE_FILES)

add_sge_base_library(
  core
  ADDITIONAL_DEPS
  fcppt_boost_interface
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_boost_interface
  ${fcppt_core_TARGET})
