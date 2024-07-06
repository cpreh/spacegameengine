fcppt_utils_load_source_files(libs/noise/files.txt SGE_NOISE_FILES)

add_sge_dummy_library(noise TRANSITIVE_SGE_DEPS sgecore
                      TRANSITIVE_ADDITIONAL_DEPS fcppt_core_interface)
