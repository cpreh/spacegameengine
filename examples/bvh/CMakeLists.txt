add_sge_console_example(
  bvh/benchmark
  COMPILE_OPTIONS
  ${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
  SGE_DEPS
  sgebvh_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  ${FCPPT_UTILS_MAIN_LINK_LIBS})

# TODO: Why is image needed here?
add_sge_example(
  bvh/planar
  SGE_DEPS
  sgebvh_interface
  sgeimage
  sgeimagecolor
  sgeinput
  sgerenderer
  sgesprite
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET})
