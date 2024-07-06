fcppt_utils_load_source_files(plugins/gdifont/files.txt SGE_GDIFONT_FILES)

find_package(awl REQUIRED)

# TODO: Change this Link to AWL so we get the unicode definitions

add_sge_plugin(
  gdifont
  SGE_DEPS
  sgefont
  sgeimage2d
  sgelog
  sgeplugin
  ADDITIONAL_DEPS
  ${awl_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
