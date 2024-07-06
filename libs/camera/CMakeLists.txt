fcppt_utils_load_source_files(libs/camera/files.txt SGE_CAMERA_FILES)

add_sge_base_library(
  camera
  HAS_IMPL_DIR
  SGE_DEPS
  sgecharconv_interface
  sgecore
  sgeinput
  sgelog
  sgeparsejson
  sgerenderer
  sgeviewport
  sgetimer_interface
  TRANSITIVE_SGE_DEPS
  sgecore_interface
  sgeinput_interface
  sgeparsejson_interface
  sgerenderer_interface
  sgetimer_interface
  sgeviewport_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface)
