include(SGECustomPath)

set(SGE_PLUGIN_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${PLUGIN_INSTALL_DIR}")

set(SGE_MEDIA_BUILD_PATH "${FCPPT_UTILS_PROJECT_SOURCE_DIR}/media")

set(SGE_MEDIA_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${MEDIA_INSTALL_DIR}")

sge_config_add_custom_path(sge media ${SGE_MEDIA_BUILD_PATH}
                           ${SGE_MEDIA_INSTALL_PATH} MEDIA_INCLUDES)

sge_config_add_custom_path(sge plugin ${SGE_PLUGIN_BUILD_PATH}
                           ${SGE_PLUGIN_INSTALL_PATH} PLUGIN_INCLUDES)

fcppt_utils_load_source_files(libs/config/files.txt SGE_CONFIG_FILES)

# TODO: Remove awl dependency here
if(WIN32)
  find_package(awl REQUIRED)

  set(SGE_CONFIG_ADDITIONAL_LIBS "${awl_TARGET}")
endif()

add_sge_base_library(
  config
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  ${SGE_CONFIG_ADDITIONAL_LIBS}
  TRANSITIVE_ADDITIONAL_DEPS
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  INCLUDE_DIRS
  ${MEDIA_INCLUDES}
  ${PLUGIN_INCLUDES})
