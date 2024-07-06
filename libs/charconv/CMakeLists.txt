fcppt_utils_load_source_files(libs/charconv/files.txt SGE_CHARCONV_FILES)

find_package(Boost 1.70.0 CONFIG REQUIRED COMPONENTS locale)

add_sge_base_library(
  charconv
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  ${Boost_LOCALE_LIBRARIES})
