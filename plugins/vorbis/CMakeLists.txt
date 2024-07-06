fcppt_utils_load_source_files(plugins/vorbis/files.txt SGE_VORBIS_FILES)

add_sge_plugin(
  vorbis
  SGE_DEPS
  sgeaudio
  sgelog
  sgemedia
  sgeplugin
  ADDITIONAL_DEPS
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  PkgConfig::VORBIS)
