fcppt_utils_load_source_files(plugins/wininput/files.txt SGE_WININPUT_FILES)

find_package(awl REQUIRED)

# TODO: Change this Link to AWL so we get the unicode definitions

add_sge_plugin(
  wininput
  SGE_DEPS
  sgeinput
  sgelog
  sgeplugin
  sgewindow
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_log_TARGET})
