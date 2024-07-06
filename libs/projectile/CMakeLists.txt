fcppt_utils_load_source_files(libs/projectile/files.txt SGE_PROJECTILE_FILES)

add_sge_base_library(
  projectile
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgeimagecolor
  sgeline_drawer
  sgelog
  sgerenderer
  TRANSITIVE_SGE_DEPS
  sgecore
  sgerenderer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ADDITIONAL_DEPS_PKGCONFIG
  PkgConfig::BULLET
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface
  fcppt_log_interface)
