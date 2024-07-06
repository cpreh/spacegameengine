fcppt_utils_load_source_files(libs/modelobj/files.txt SGE_MODELOBJ_FILES)

add_sge_base_library(
  "model/obj"
  HAS_IMPL_DIR
  SGE_DEPS
  sgecharconv
  sgecore
  sgeimagecolor
  sgelog
  sgerenderer
  TRANSITIVE_SGE_DEPS
  sgecharconv_interface
  sgecore
  sgeimagecolor
  sgerenderer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
