fcppt_utils_load_source_files(plugins/audio_null/files.txt SGE_AUDIO_NULL_FILES)

add_sge_plugin(audio_null SGE_DEPS sgeaudio sgeplugin ADDITIONAL_DEPS
               ${fcppt_log_TARGET})
