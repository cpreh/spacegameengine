fcppt_utils_load_source_files(libs/systems/files.txt SGE_SYSTEMS_FILES)

find_package(awl REQUIRED)

add_sge_base_library(
  systems
  HAS_IMPL_DIR
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgecore
  sgefont
  sgeimage2d
  sgeinput
  sgelog
  sgemedia
  sgeparse
  sgeparseini
  sgeplugin
  sgerenderer
  sgeviewport
  sgewindow
  TRANSITIVE_SGE_DEPS
  sgeaudio_interface
  sgecore_interface
  sgefont_interface
  sgeimage2d_interface
  sgeinput_interface
  sgelog_interface
  sgemedia_interface
  sgeplugin_interface
  sgerenderer_interface
  sgeviewport_interface
  sgewindow_interface
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  fcppt_parse_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  awl_interface
  fcppt_boost_interface
  fcppt_core_interface
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
