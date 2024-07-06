fcppt_utils_load_source_files(plugins/wave/files.txt SGE_WAVE_FILES)

add_sge_plugin(
  wave
  SGE_DEPS
  sgeaudio
  sgelog
  sgemedia
  sgeplugin
  ADDITIONAL_DEPS
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET})
