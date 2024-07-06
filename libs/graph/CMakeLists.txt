fcppt_utils_load_source_files(libs/graph/files.txt SGE_GRAPH_FILES)

add_sge_base_library(
  "graph"
  HAS_IMPL_DIR
  SGE_DEPS
  sgeimage
  sgeimagecolor
  sgeimage2d
  sgerenderer
  sgesprite
  sgetexture
  TRANSITIVE_SGE_DEPS
  sgeimagecolor_interface
  sgerenderer_interface
  sgesprite_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
