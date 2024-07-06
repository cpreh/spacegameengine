fcppt_utils_load_source_files(libs/cursor/files.txt SGE_CURSOR_FILES)

add_sge_base_library(
  cursor
  HAS_IMPL_DIR
  SGE_DEPS
  sgeinput
  sgerenderer
  sgesprite
  sgetexture
  TRANSITIVE_SGE_DEPS
  sgeinput_interface
  sgerenderer_interface
  sgetexture_interface
  ADDITIONAL_DEPS
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
