fcppt_utils_load_source_files(libs/renderercg/files.txt SGE_RENDERERCG_FILES)

add_sge_base_library(
  "renderer/cg"
  SGE_DEPS
  sgerenderer
  TRANSITIVE_SGE_DEPS
  sgerenderer_interface
  ADDITIONAL_DEPS
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
