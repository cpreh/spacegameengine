fcppt_utils_load_source_files(libs/imageds/files.txt SGE_IMAGEDS_FILES)

find_package(mizuiro REQUIRED)

add_sge_base_library(
  "image/ds"
  HAS_IMPL_DIR
  SGE_DEPS
  sgeimage
  TRANSITIVE_SGE_DEPS
  sgeimage_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  mizuiro_interface
  fcppt_core_interface
  COMPILE_DEFINITIONS
  ${IMAGE_DEFINITIONS}
  IMPLEMENT_FROM
  image)
