fcppt_utils_load_source_files(libs/image/files.txt SGE_IMAGE_FILES)

find_package(mizuiro REQUIRED)

option(
  ENABLE_STATIC_COPY_AND_CONVERT
  "Use static copy and convert which will produce bigger but probably faster code"
  OFF)

if(ENABLE_STATIC_COPY_AND_CONVERT)
  set(SGE_IMAGE_STATIC_COPY_AND_CONVERT TRUE)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/sge/image/impl/config.hpp)

sge_generate_instantiate_symbol_header(image)

add_sge_base_library(
  image
  HAS_IMPL_DIR
  SGE_DEPS
  sgecore
  TRANSITIVE_SGE_DEPS
  sgecore
  USE_IMPL_INCLUDE_OF
  core
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  mizuiro_interface
  TRANSITIVE_ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_boost_interface
  mizuiro_interface
  INCLUDE_DIRS
  "${CMAKE_CURRENT_BINARY_DIR}/include")
