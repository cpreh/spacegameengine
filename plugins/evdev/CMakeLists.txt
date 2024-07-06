fcppt_utils_load_source_files(plugins/evdev/files.txt SGE_EVDEV_FILES)

find_package(awl REQUIRED)

add_sge_plugin(
  evdev
  SGE_DEPS
  sgeinput
  sgelog
  sgeplugin
  sgewindow
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
