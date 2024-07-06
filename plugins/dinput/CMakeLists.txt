fcppt_utils_load_source_files(plugins/dinput/files.txt SGE_DINPUT_FILES)

find_package(awl REQUIRED)

add_sge_plugin(
  "dinput"
  SGE_DEPS
  sgeinput
  sgelog
  sgeplugin
  sgewindow
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_log_TARGET}
  ${DINPUT_LIBRARIES}
  SYSTEM_INCLUDE_DIRS
  ${DINPUT_INCLUDE_DIRS})
