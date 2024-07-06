fcppt_utils_load_source_files(libs/fontbitmap/files.txt SGE_FONTBITMAP_FILES)

add_sge_base_library(
  "font/bitmap"
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgefont
  sgeimagecolor
  sgeimage2d
  sgelog
  sgeparsejson
  TRANSITIVE_SGE_DEPS
  sgefont_interface
  sgeimage2d_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_log_interface)
