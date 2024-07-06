fcppt_utils_load_source_files(libs/bvh/files.txt SGE_BVH_FILES)

add_sge_dummy_library(bvh TRANSITIVE_SGE_DEPS sgecore
                      TRANSITIVE_ADDITIONAL_DEPS fcppt_core_interface)
