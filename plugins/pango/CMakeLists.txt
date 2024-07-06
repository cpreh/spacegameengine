fcppt_utils_load_source_files(plugins/pango/files.txt SGE_PANGO_FILES)

add_sge_plugin(
  pango
  SGE_DEPS
  sgecharconv
  sgefont
  sgeimagecolor
  sgeimage2d
  sgeplugin
  ADDITIONAL_DEPS
  PkgConfig::PANGO
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
