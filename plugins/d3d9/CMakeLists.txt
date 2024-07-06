fcppt_utils_load_source_files(plugins/d3d9/files.txt SGE_D3D9_BASE_FILES)

find_package(awl REQUIRED)

set(SGE_D3D9_FILES "${SGE_D3D9_BASE_FILES}")

set(SGE_D3D9_SGE_DEPS
    sgeimage2d
    sgeimage3d
    sgeimagecolor
    sgeimageds
    sgeimageds2d
    sgelog
    sgeplugin
    sgerenderer
    sgewindow)

set(SGE_D3D9_ADDITIONAL_DEPS ${awl_TARGET} ${D3D9_LIBRARIES})

# For some reason, it's not possible to ignore these warnings in gcc via
# push/pop
if(CMAKE_COMPILER_IS_GNUCXX AND NOT FCPPT_UTILS_COMPILER_IS_CLANGPP)
  set(SGE_D3D9_COMPILE_FLAGS "-Wno-comment" "-Wno-unknown-pragmas")
endif()

if(ENABLE_CG)
  list(APPEND SGE_D3D9_ADDITIONAL_INCLUDE_DIRS
      ${Cg_INCLUDE_DIRS}
      ${CMAKE_CURRENT_SOURCE_DIR}/cg/include)

  fcppt_utils_load_source_files(plugins/d3d9/cg/files.txt SGE_D3D9_CG_FILES)

  list(APPEND SGE_D3D9_FILES ${SGE_D3D9_CG_FILES})

  list(APPEND SGE_D3D9_ADDITIONAL_DEPS ${Cg_LIBRARIES} ${Cg_D3D9_LIBRARIES})

  list(APPEND SGE_D3D9_SGE_DEPS sgecg sgerenderercg)
endif()

add_sge_plugin(
  "d3d9"
  SGE_DEPS
  ${SGE_D3D9_SGE_DEPS}
  ADDITIONAL_DEPS
  ${SGE_D3D9_ADDITIONAL_DEPS}
  ${fcppt_log_TARGET}
  SYSTEM_INCLUDE_DIRS
  ${D3D9_INCLUDE_DIRS}
  INCLUDE_DIRS
  ${SGE_D3D9_ADDITIONAL_INCLUDE_DIRS}
  COMPILE_FLAGS
  ${SGE_D3D9_COMPILE_FLAGS})
