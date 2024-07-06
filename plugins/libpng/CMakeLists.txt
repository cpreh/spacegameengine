fcppt_utils_load_source_files(plugins/libpng/files.txt SGE_LIBPNG_FILES)

add_sge_plugin(
  libpng
  SGE_DEPS
  sgeimage
  sgeimagecolor
  sgeimage2d
  sgelog
  sgemedia
  sgeplugin
  ADDITIONAL_DEPS
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  ${PNG_LIBRARIES}
  INCLUDE_DIRS
  ${PNG_INCLUDE_DIR}
  COMPILE_DEFINITIONS
  ${PNG_DEFINITIONS})
