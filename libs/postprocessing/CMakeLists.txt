fcppt_utils_load_source_files(libs/postprocessing/files.txt SGE_POSTPROCESSING_FILES)

add_sge_base_library(
  "postprocessing"
  SGE_DEPS
  sgecg
  sgeconfig
  sgecore
  sgerenderer
  sgerenderercg
  sgeshader
  sgeviewport
  sgeimagecolor_interface
  TRANSITIVE_SGE_DEPS
  sgerenderer_interface
  sgeshader_interface
  sgeviewport_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  SYSTEM_INCLUDE_DIRS
  "${Cg_INCLUDE_DIRS}")
