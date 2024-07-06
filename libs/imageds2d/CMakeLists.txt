fcppt_utils_load_source_files(libs/imageds2d/files.txt SGE_IMAGEDS2D_FILES)

find_package(mizuiro REQUIRED)

add_sge_base_library(
  imageds2d
  SGE_DEPS
  sgeimage
  sgeimageds
  TRANSITIVE_SGE_DEPS
  sgeimage_interface
  sgeimageds_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  mizuiro_interface
  IMPLEMENT_FROM
  image
  USE_IMPL_INCLUDE_OF
  imageds)
