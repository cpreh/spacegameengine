fcppt_utils_load_source_files(libs/consolegfx/files.txt SGE_CONSOLEGFX_FILES)

add_sge_base_library(
  "console/gfx"
  SGE_DEPS
  sgeconsole
  sgecore
  sgefont
  sgefontdraw
  sgeimagecolor
  sgeinput
  sgerenderer
  TRANSITIVE_SGE_DEPS
  sgeconsole_interface
  sgefont_interface
  sgeimagecolor_interface
  sgeinput_interface
  sgerenderer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  TRANSITIVE_ADDITIONAL_DEPS
  fcppt_core_interface)
