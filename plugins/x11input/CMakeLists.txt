fcppt_utils_load_source_files(plugins/x11input/files.txt SGE_X11INPUT_FILES)

find_package(awl REQUIRED)

add_sge_plugin(
  x11input
  SGE_DEPS
  sgeinput
  sgelog
  sgeplugin
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${awl_TARGET}
  PkgConfig::XINPUT)
