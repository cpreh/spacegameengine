fcppt_utils_load_source_files(libs/imagecolor/files.txt SGE_IMAGECOLOR_FILES)

find_package(mizuiro REQUIRED)

add_sge_base_library(
  "image/color"
  HAS_IMPL_DIR
  SGE_DEPS
  sgeimage
  TRANSITIVE_SGE_DEPS
  sgeimage_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  mizuiro_interface
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  mizuiro_interface
  fcppt_core_interface
  IMPLEMENT_FROM
  image)
