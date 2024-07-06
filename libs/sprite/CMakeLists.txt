fcppt_utils_load_source_files(libs/sprite/files.txt SGE_SPRITE_FILES)

add_sge_base_library(
  sprite
  SGE_DEPS
  sgerenderer
  sgetexture_interface
  TRANSITIVE_SGE_DEPS
  sgerenderer
  sgetexture
  sgeimage_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_boost_interface)
