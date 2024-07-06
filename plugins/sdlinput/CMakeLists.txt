fcppt_utils_load_source_files(plugins/sdlinput/files.txt SGE_SDLINPUT_FILES)

find_package(SDL2 REQUIRED)

add_sge_plugin(
  sdlinput
  SGE_DEPS
  sgeinput
  sgelog
  sgeplugin
  sgewindow
  ADDITIONAL_DEPS
  ${awl_TARGET}
  fcppt_core_interface
  fcppt_log_interface
  ${SDL2_LIBRARIES}
  SYSTEM_INCLUDE_DIRS
  ${SDL2_INCLUDE_DIRS})
