find_package(awl REQUIRED)

include(AwlMainGenerator)

find_package(mizuiro REQUIRED)

set(SGE_INSTALL_EXAMPLE_DIR
    "${CMAKE_INSTALL_BINDIR}"
    CACHE STRING "Custom example installation directory")

function(add_sge_example_base PATH_NAME)
  set(SINGLE_ARGS CONSOLE_EXAMPLE)

  set(MULTI_ARGS SGE_DEPS ADDITIONAL_DEPS COMPILE_OPTIONS)

  cmake_parse_arguments("" "" "${SINGLE_ARGS}" "${MULTI_ARGS}" ${ARGN})

  sge_check_optional_deps("The ${PATH_NAME} example" "${_SGE_DEPS}")

  string(REPLACE "/" "_" FULL_NAME ${PATH_NAME})

  set(FULL_NAME "sge_example_${FULL_NAME}")

  set(SOURCE_FILE "${FCPPT_UTILS_PROJECT_SOURCE_DIR}/examples/${PATH_NAME}.cpp")

  if(_CONSOLE_EXAMPLE)
    add_executable(${FULL_NAME} ${SOURCE_FILE})
  else()
    awl_utils_add_portable_executable(${FULL_NAME} "example_main"
                                      ${SOURCE_FILE})

    target_link_libraries(${FULL_NAME} PRIVATE ${awl_TARGET})
  endif()

  fcppt_utils_set_target_folder(${FULL_NAME} examples ${PATH_NAME})

  fcppt_utils_set_target_compiler_flags(${FULL_NAME})

  transform_sge_link_targets("${_SGE_DEPS}" SGE_LIBRARIES_RESULT)

  target_compile_options("${FULL_NAME}" PRIVATE ${_COMPILE_OPTIONS})

  target_include_directories(
    "${FULL_NAME}" PRIVATE ${FCPPT_UTILS_PROJECT_SOURCE_DIR}/examples/include)

  target_link_libraries(${FULL_NAME} PRIVATE ${_ADDITIONAL_DEPS}
                                             ${SGE_LIBRARIES_RESULT})

  install(TARGETS ${FULL_NAME} DESTINATION "${SGE_INSTALL_EXAMPLE_DIR}")
endfunction()

function(add_sge_example PATH_NAME)
  set(MULTI_ARGS SGE_DEPS ADDITIONAL_DEPS COMPILE_OPTIONS)

  cmake_parse_arguments("" "" "" "${MULTI_ARGS}" ${ARGN})

  add_sge_example_base(
    "${PATH_NAME}"
    SGE_DEPS
    ${_SGE_DEPS}
    ADDITIONAL_DEPS
    ${_ADDITIONAL_DEPS}
    COMPILE_OPTIONS
    ${_COMPILE_OPTIONS}
    CONSOLE_EXAMPLE
    FALSE)
endfunction()

function(add_sge_console_example PATH_NAME)
  set(MULTI_ARGS SGE_DEPS ADDITIONAL_DEPS COMPILE_OPTIONS)

  cmake_parse_arguments("" "" "" "${MULTI_ARGS}" ${ARGN})

  add_sge_example_base(
    "${PATH_NAME}"
    SGE_DEPS
    ${_SGE_DEPS}
    ADDITIONAL_DEPS
    ${_ADDITIONAL_DEPS}
    COMPILE_OPTIONS
    ${_COMPILE_OPTIONS}
    CONSOLE_EXAMPLE
    TRUE)
endfunction()

add_sge_example(
  anaglyph
  SGE_DEPS
  sgecamera
  sgeconfig
  sgeimagecolor
  sgeinput
  sgelog
  sgemodelmd3
  sgerenderer
  sgesystems
  sgetimer_interface
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  app_path SGE_DEPS sgeconfig ADDITIONAL_DEPS ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

# FIXME add_sge_console_example( audio_minimal SGE_DEPS sgeaudio sgeconfig
# sgemedia_interface sgelog sgeplugin ADDITIONAL_DEPS ${fcppt_core_TARGET}
# ${fcppt_log_TARGET} ${FCPPT_UTILS_FILESYSTEM_LIBRARIES} )

add_sge_example(
  bitmapfont
  SGE_DEPS
  sgeconfig
  sgefont
  sgefontbitmap
  sgefontdraw
  sgeimagecolor
  sgemedia_interface
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

# FIXME add_sge_console_example( caps SGE_DEPS sgeconfig sgelog sgeplugin
# sgerenderer sgewindow ADDITIONAL_DEPS ${awl_TARGET} ${fcppt_core_TARGET}
# ${fcppt_log_TARGET} )

add_sge_console_example(
  color_string_convert
  SGE_DEPS
  sgeimage
  sgeimagecolor
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  ${FCPPT_UTILS_MAIN_LINK_LIBS}
  COMPILE_OPTIONS
  ${FCPPT_UTILS_MAIN_COMPILE_OPTIONS})

add_sge_console_example(
  config SGE_DEPS sgeconfig ADDITIONAL_DEPS ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  console
  SGE_DEPS
  sgeconfig
  sgeconsole
  sgeconsolegfx
  sgefont
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgemedia_interface
  sgerenderer
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  custom_cursor
  SGE_DEPS
  sgeconfig
  sgecursor
  sgeimagecolor
  sgeinput
  sgelog
  sgemedia_interface
  sgerenderer
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  display_mode
  SGE_DEPS
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET})

add_sge_example(
  doppler
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgelog
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  font
  SGE_DEPS
  sgefont
  sgefontdraw
  sgeimagecolor
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET})

add_sge_example(
  fullscreen
  SGE_DEPS
  sgeimagecolor
  sgelog
  sgerenderer
  sgesystems
  sgetimer_interface
  sgeviewport_interface
  sgewindow
  sgetimer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  graph
  SGE_DEPS
  sgegraph
  sgeimagecolor
  sgeimage2d_interface
  sgelog
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  ini
  SGE_DEPS
  sgeparse
  sgeparseini
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_parse_interface)

add_sge_example(
  input
  SGE_DEPS
  sgeconsole
  sgeconsolegfx
  sgefont
  sgeimagecolor
  sgeinput
  sgelog
  sgerenderer
  sgesystems
  sgetimer
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(input_only SGE_DEPS sgesystems sgewindow ADDITIONAL_DEPS
                ${fcppt_core_TARGET})

add_sge_example(
  intrusivesprite
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  json
  SGE_DEPS
  sgeparse
  sgeparsejson
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_parse_interface)

add_sge_example(
  lighting
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  line_drawer
  SGE_DEPS
  sgefont
  sgefontdraw
  sgeimagecolor
  sgeinput
  sgeline_drawer
  sgerenderer
  sgesystems
  sgetimer
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  line_of_sight
  SGE_DEPS
  sgebresenham_interface
  sgeimagecolor
  sgeinput
  sgerenderer
  sgesprite
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  add_sge_example(
    linux_stats
    SGE_DEPS
    sgefont
    sgefontdraw
    sgegraph
    sgeimagecolor
    sgeimage2d_interface
    sgelog
    sgerenderer
    sgesystems
    sgetimer
    sgeviewport
    sgewindow
    ADDITIONAL_DEPS
    ${fcppt_core_TARGET}
    ${fcppt_filesystem_TARGET}
    ${fcppt_options_TARGET}
    fcppt_log_interface
    ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
endif()

add_sge_console_example(
  log_path SGE_DEPS sgeconfig ADDITIONAL_DEPS ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  mergeimage
  COMPILE_OPTIONS
  ${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
  SGE_DEPS
  sgecore
  sgeimage_interface
  sgeimagecolor
  sgeimage2d
  sgemedia_interface
  sgesystems
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  ${FCPPT_UTILS_MAIN_LINK_LIBS}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  multi_texture
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgelog
  sgemedia_interface
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  multi_texture_sprite
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  noise
  SGE_DEPS
  sgeimage_interface
  sgeimagecolor
  sgeimage2d
  sgelog
  sgenoise_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  mizuiro_interface
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  obj_loader
  SGE_DEPS
  sgecharconv
  sgeconfig
  sgemodelobj
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  opengl
  SGE_DEPS
  sgeimage_interface
  sgerenderer
  sgerendereropengl
  sgesystems
  sgeviewport
  sgewindow_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  ortho_view
  SGE_DEPS
  sgecamera
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgelog
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgetimer_interface
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  point_sprite
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgelog
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  plugin
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgefont
  sgeimage2d
  sgeinput
  sgelog
  sgeplugin
  sgerenderer
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  projectile/main
  SGE_DEPS
  sgeimagecolor
  sgeinput
  sgelog
  sgeprojectile
  sgerenderer
  sgesystems
  sgetimer_interface
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  render_text
  SGE_DEPS
  sgefont
  sgeimage2d
  sgelog
  sgesystems
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${fcppt_options_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  ${FCPPT_UTILS_MAIN_LINK_LIBS}
  COMPILE_OPTIONS
  ${FCPPT_UTILS_MAIN_COMPILE_OPTIONS})

add_sge_console_example(
  resource_tree
  SGE_DEPS
  sgeconfig
  sgeresource_tree
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  scenic
  SGE_DEPS
  sgecamera
  sgeconfig
  sgegraph
  sgeimagecolor
  sgeinput
  sgemedia_interface
  sgeparsejson
  sgerenderer
  sgescenic
  sgesystems
  sgetimer_interface
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${fcppt_options_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  screenshot
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  sound
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgelog
  sgemedia_interface
  sgesystems
  sgetimer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  sprite_color
  SGE_DEPS
  sgeimagecolor
  sgelog
  sgerenderer
  sgesprite
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  sprite_color_texture
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgelog
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  sprite_move
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  stencil
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  swoosh
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgegraph
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgelog
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  target
  SGE_DEPS
  sgeconfig
  sgeimagecolor
  sgeimage2d
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  texture_filter
  SGE_DEPS
  sgecamera
  sgefont
  sgefontdraw
  sgeimage_interface
  sgeimagecolor
  sgeimage2d
  sgeinput
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgetimer
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  tutorial/sound_01
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgemedia_interface
  sgesystems
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_console_example(
  tutorial/sound_02
  SGE_DEPS
  sgeaudio
  sgeconfig
  sgemedia_interface
  sgesystems
  sgetimer_interface
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  tutorial/sprite_03
  SGE_DEPS
  sgeconfig
  sgemedia_interface
  sgerenderer
  sgesprite
  sgesystems
  sgetexture
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  vertex
  SGE_DEPS
  sgeimagecolor
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  vertex_index
  SGE_DEPS
  sgeimagecolor
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  vertex_planar
  SGE_DEPS
  sgeimagecolor
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  vertex_texture
  SGE_DEPS
  sgeconfig
  sgemedia_interface
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  volume_texture
  SGE_DEPS
  sgecamera
  sgeimage_interface
  sgeimagecolor
  sgeimage3d
  sgeinput
  sgenoise_interface
  sgerenderer
  sgesystems
  sgetimer_interface
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  mizuiro_interface
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_sge_example(
  window_without_input
  SGE_DEPS
  sgeimagecolor
  sgerenderer
  sgesystems
  sgeviewport
  sgewindow
  ADDITIONAL_DEPS
  ${fcppt_core_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})

add_subdirectory(bvh)

add_subdirectory(cg)

add_subdirectory(gui)

add_subdirectory(opencl)

add_subdirectory(rucksack)
