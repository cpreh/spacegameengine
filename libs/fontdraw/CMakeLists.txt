fcppt_utils_load_source_files(libs/fontdraw/files.txt SGE_FONTDRAW_FILES)

add_sge_base_library(
  "font/draw"
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgefont
  sgeimagecolor
  sgeimage2d
  sgerenderer
  sgesprite
  sgetexture
  TRANSITIVE_SGE_DEPS
  sgefont_interface
  sgeimagecolor_interface
  sgerenderer_interface
  sgetexture_interface
  ADDITIONAL_DEPS
  fcppt_core_interface)
