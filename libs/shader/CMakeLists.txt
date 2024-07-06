fcppt_utils_load_source_files(libs/shader/files.txt SGE_SHADER_FILES)

add_sge_base_library(
  "shader"
  SGE_DEPS
  sgecg
  sgecore
  sgerenderer
  sgerenderercg
  TRANSITIVE_SGE_DEPS
  sgecore
  sgecg_interface
  sgerenderer_interface
  sgerenderercg_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  TRANSITIVE_SYSTEM_INCLUDE_DIRS
  ${Cg_INCLUDE_DIRS})
