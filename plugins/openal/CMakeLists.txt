fcppt_utils_load_source_files(plugins/openal/files.txt SGE_OPENAL_FILES)

add_sge_plugin(
  openal
  SGE_DEPS
  sgeaudio
  sgelog
  sgeplugin
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${OPENAL_LIBRARY}
  SYSTEM_INCLUDE_DIRS
  ${OPENAL_INCLUDE_DIR})
