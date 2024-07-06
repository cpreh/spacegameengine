fcppt_utils_load_source_files(libs/image3d/files.txt SGE_IMAGE3D_FILES)

find_package(mizuiro REQUIRED)

add_sge_base_library(
  image3d
  SGE_DEPS
  sgeimage
  sgeimagecolor
  TRANSITIVE_SGE_DEPS
  sgeimage_interface
  sgeimagecolor_interface
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  fcppt_core_interface
  TRANSITIVE_ADDITIONAL_DEPS
  mizuiro_interface
  fcppt_core_interface
  INCLUDE_DIRS
  "${FCPPT_UTILS_PROJECT_BINARY_DIR}/libs/image/include"
  IMPLEMENT_FROM
  image
  USE_IMPL_INCLUDE_OF
  imagecolor
  COMPILE_FLAGS
  ${SGE_MSVC_BIGOBJ_FLAGS})
