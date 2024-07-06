fcppt_utils_load_source_files(plugins/wlinput/files.txt SGE_WLINPUT_FILES)

find_package(awl REQUIRED)

add_sge_plugin(
  wlinput
  SGE_DEPS
  sgecharconv
  sgeinput
  sgelog
  sgeplugin
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${awl_TARGET}
  PkgConfig::WAYLAND_INPUT)
