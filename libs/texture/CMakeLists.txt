fcppt_utils_load_source_files(libs/texture/files.txt SGE_TEXTURE_FILES)

add_sge_base_library(
  texture
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgeimage2d
  sgelog
  sgerenderer
  sgeimage_interface
  TRANSITIVE_SGE_DEPS
  sgecore
  sgeimage_interface
  sgeimage2d_interface
  sgerenderer_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_boost_interface
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  USE_IMPL_INCLUDE_OF
  renderer)
