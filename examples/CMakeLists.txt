MACRO (ADD_SGE_EXAMPLE EXAMPLE_NAME ADDITONAL_LIBRARIES)
	# Replace slashes
	STRING(REPLACE "/" "" FULL_NAME ${EXAMPLE_NAME})

	SET(FULL_NAME sge${FULL_NAME}example)

	ADD_EXECUTABLE (${FULL_NAME} ${EXAMPLE_NAME}.cpp)

	TARGET_LINK_LIBRARIES (
		${FULL_NAME}
		sgecore
		${ADDITONAL_LIBRARIES}
	)

	INSTALL (TARGETS ${FULL_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
ENDMACRO ()

FIND_PACKAGE(
	Boost 1.41.0 REQUIRED
	COMPONENTS
	program_options
)

ADD_SGE_EXAMPLE(anim "sgesprite;sgesystems;sgetexture;sgetime")
ADD_SGE_EXAMPLE(appdir "sgeconfig")
ADD_SGE_EXAMPLE(bitmapfont "sgefonttext;sgesystems")
ADD_SGE_EXAMPLE(bloom "")
ADD_SGE_EXAMPLE(caps "sgeconfig")
ADD_SGE_EXAMPLE(cie "")
ADD_SGE_EXAMPLE(collision "sgesprite;sgesystems;sgetime")
ADD_SGE_EXAMPLE(configdir "sgeconfig")
ADD_SGE_EXAMPLE(doppler "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(fullscreen "sgesystems;sgetime")
ADD_SGE_EXAMPLE(ini "sgeparse")
ADD_SGE_EXAMPLE(intrusivesprite "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(json "sgeparse")
ADD_SGE_EXAMPLE(mergeimage "sgesystems")
#ADD_SGE_EXAMPLE(model)
ADD_SGE_EXAMPLE(modifier "sgesystems")
ADD_SGE_EXAMPLE(plugin "sgeconfig")
#ADD_SGE_EXAMPLE(pool)
ADD_SGE_EXAMPLE(screenshot "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(shader/raw "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(spritecolor "sgesprite;sgesystems")
ADD_SGE_EXAMPLE(sound "${Boost_PROGRAM_OPTIONS_LIBRARY};sgesystems;sgetime")
ADD_SGE_EXAMPLE(target "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(vertex "sgesystems")

ADD_SGE_EXAMPLE(tutorial/font "sgefonttext;sgesprite;sgesystems")
#ADD_SGE_EXAMPLE(tutorial/sound_01)
#ADD_SGE_EXAMPLE(tutorial/sound_02)
#ADD_SGE_EXAMPLE(tutorial/sound_03)
ADD_SGE_EXAMPLE(tutorial/tutorial_01 "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(tutorial/tutorial_02 "sgesprite;sgesystems;sgetexture")

ADD_SGE_EXAMPLE(cg1/ex04 "sgesystems;sgetime")

#IF(SGE_HAVE_X11)
#	ADD_SGE_EXAMPLE(asio_window)
#ENDIF()

# TODO: this should be part of the macro
#IF (NOT MSVC)
#	TARGET_LINK_LIBRARIES (sgesoundexample ${Boost_program_options_LIBRARIES})
#ENDIF ()

IF (ENABLE_CONSOLE)
	ADD_SGE_EXAMPLE(console "sgeconsole;sgesystems")
ENDIF()

IF (ENABLE_GUI)
	ADD_SGE_EXAMPLE(edit "sgegui;sgesystems")
	ADD_SGE_EXAMPLE(grid "sgegui;sgesystems")
	ADD_SGE_EXAMPLE(gui "sgegui;sgesystems")
ENDIF ()

#ADD_EXECUTABLE (islandexample island/main.cpp quadtree/quadtree.cpp quadtree/mathstuff.cpp island/island_extractor.cpp island/skydome.cpp)
#TARGET_LINK_LIBRARIES (islandexample sgecore)
#INSTALL (TARGETS islandexample DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

#ADD_EXECUTABLE (skydomeexample island/skydome.cpp island/skydome_examplecase.cpp)
#TARGET_LINK_LIBRARIES (skydomeexample sgecore)
#INSTALL (TARGETS skydomeexample DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
