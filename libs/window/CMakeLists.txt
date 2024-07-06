fcppt_utils_load_source_files(libs/window/files.txt SGE_WINDOW_FILES)

find_package(awl REQUIRED)

add_sge_base_library(
  window
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  awl_interface
  fcppt_core_interface)
