remove_definitions("-D SGE_PLUGIN_INSTANTIATE_EXPORTS")

fcppt_utils_load_source_files(libs/rendereropengl/files.txt SGE_RENDEREROPENGL_FILES)

add_sge_base_library(
  "renderer/opengl"
  ADDITIONAL_DEPS
  sgecore_interface
  "${OPENGL_gl_LIBRARY}"
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  sgecore_interface
  fcppt_core_interface
  INCLUDE_DIRS
  ${OPENGL_INCLUDE_DIR}
  TRANSITIVE_INCLUDE_DIRS
  ${OPENGL_INCLUDE_DIR})
