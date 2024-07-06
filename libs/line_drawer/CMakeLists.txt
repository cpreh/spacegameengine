fcppt_utils_load_source_files(libs/line_drawer/files.txt SGE_LINE_DRAWER_FILES)

add_sge_base_library(
  line_drawer
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgeimagecolor
  sgerenderer
  TRANSITIVE_SGE_DEPS
  sgeimagecolor_interface
  sgerenderer_interface
  ADDITIONAL_DEPS
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
