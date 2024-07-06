fcppt_utils_load_source_files(libs/plugin/files.txt SGE_PLUGIN_FILES)

sge_generate_instantiate_symbol_header(plugin)

# TODO: Remove awl dependency here
if(WIN32)
  find_package(awl REQUIRED)

  set(SGE_PLUGIN_ADDITIONAL_LIBS "${awl_TARGET}")

  set(SGE_PLUGIN_TRANSITIVE_ADDITIONAL_LIBS awl_interface)
else()
  find_library(POSIX_DL_LIBRARY NAMES dl)

  set(SGE_PLUGIN_ADDITIONAL_LIBS "${POSIX_DL_LIBRARY}")
endif()

add_sge_base_library(
  plugin
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  sgelog
  TRANSITIVE_SGE_DEPS
  sgecore
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  ${SGE_PLUGIN_ADDITIONAL_LIBS}
  TRANSITIVE_ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${SGE_PLUGIN_TRANSITIVE_ADDITIONAL_LIBS})
