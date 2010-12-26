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
	Boost 1.45.0 REQUIRED
	COMPONENTS
	program_options
)

ADD_SGE_EXAMPLE(anim "sgesprite;sgesystems;sgetexture;sgetime")
ADD_SGE_EXAMPLE(appdir "sgeconfig")
ADD_SGE_EXAMPLE(asio_window "sgesystems")
ADD_SGE_EXAMPLE(bitmapfont "sgefontbitmap;sgefonttext;sgesystems")
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
#ADD_SGE_EXAMPLE(model "sgesystems")
ADD_SGE_EXAMPLE(modifier "sgesystems")
ADD_SGE_EXAMPLE(plugin "sgeconfig")
ADD_SGE_EXAMPLE(pointsprite "sgesystems;sgesprite")
ADD_SGE_EXAMPLE(pool "sgesystems;sgetime")
ADD_SGE_EXAMPLE(screenshot "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(shader/raw "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(spritecolor "sgesprite;sgesystems")
ADD_SGE_EXAMPLE(sound "${Boost_PROGRAM_OPTIONS_LIBRARY};sgesystems;sgetime")
ADD_SGE_EXAMPLE(target "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(vertex "sgesystems")
ADD_SGE_EXAMPLE(texture3d "${Boost_PROGRAM_OPTIONS_LIBRARY};sgesystems;sgetexture;sgecamera;sgeshader;sgetime;sgeconfig")
ADD_SGE_EXAMPLE(savetexture "sgesystems;sgesprite;sgetexture;sgeshader")
ADD_SGE_EXAMPLE(tutorial/font "sgefonttext;sgesprite;sgesystems")
ADD_SGE_EXAMPLE(tutorial/sound_01 "sgeconfig;sgesystems")
ADD_SGE_EXAMPLE(tutorial/sound_02 "sgeconfig;sgesystems")
ADD_SGE_EXAMPLE(tutorial/sound_03 "sgeconfig;sgesystems;sgetime")
ADD_SGE_EXAMPLE(tutorial/sprite_01 "sgesprite;sgesystems;sgetexture")
ADD_SGE_EXAMPLE(tutorial/sprite_02 "sgesprite;sgesystems;sgetexture")

ADD_SGE_EXAMPLE(cg1/ex04 "sgesystems;sgetime")

IF (ENABLE_CONSOLE)
	ADD_SGE_EXAMPLE(console "sgeconsole;sgesystems")
ENDIF()

IF (ENABLE_GUI)
	ADD_SGE_EXAMPLE(edit "sgegui;sgesystems")
	ADD_SGE_EXAMPLE(grid "sgegui;sgesystems")
	ADD_SGE_EXAMPLE(gui "sgegui;sgesystems")
ENDIF ()
