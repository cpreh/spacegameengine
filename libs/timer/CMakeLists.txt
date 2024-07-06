fcppt_utils_load_source_files(libs/timer/files.txt SGE_TIMER_FILES)

add_sge_base_library(timer ADDITIONAL_DEPS ${fcppt_core_TARGET}
                     TRANSITIVE_ADDITIONAL_DEPS fcppt_core_interface)
