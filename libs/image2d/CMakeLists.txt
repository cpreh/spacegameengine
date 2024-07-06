fcppt_utils_load_source_files(libs/image2d/files.txt SGE_IMAGE2D_FILES)

find_package(mizuiro REQUIRED)

add_sge_base_library(
  image2d
  HAS_IMPL_DIR
  SGE_DEPS
  sgeimage
  sgeimagecolor
  sgelog
  sgemedia
  sgeplugin
  TRANSITIVE_SGE_DEPS
  sgeimage_interface
  sgeimagecolor_interface
  sgemedia_interface
  sgeplugin_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  mizuiro_interface
  fcppt_core_interface
  fcppt_log_interface
  INCLUDE_DIRS
  "${FCPPT_UTILS_PROJECT_BINARY_DIR}/libs/image/include"
  IMPLEMENT_FROM
  image
  media
  plugin
  USE_IMPL_INCLUDE_OF
  imagecolor
  COMPILE_FLAGS
  ${SGE_MSVC_BIGOBJ_FLAGS})
