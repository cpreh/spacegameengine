FIND_PACKAGE(
	Boost 1.45.0 REQUIRED
	COMPONENTS
	program_options
)

FUNCTION(
	ADD_SGE_EXAMPLE
	EXAMPLE_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
)
	FOREACH(
		SGELIB
		${SGE_LIBRARIES}
	)
		STRING(TOUPPER ${SGELIB} SGELIB_UPPER)

		IF(NOT ENABLE_${SGELIB_UPPER})
			MESSAGE(
				STATUS
				"${EXAMPLE_NAME} example will not be built because ${SGELIB} is not enabled!"
			)

			RETURN()
		ENDIF()

		SET(SGE_LIBRARIES_FULL "${SGE_LIBRARIES_FULL};sge${SGELIB}")
	ENDFOREACH()

	STRING(REPLACE "/" "" FULL_NAME ${EXAMPLE_NAME})

	SET(FULL_NAME sge${FULL_NAME}example)

	ADD_EXECUTABLE (${FULL_NAME} ${EXAMPLE_NAME}.cpp)

	TARGET_LINK_LIBRARIES (
		${FULL_NAME}
		sgecore
		${ADDITIONAL_LIBRARIES}
		${SGE_LIBRARIES_FULL}
	)

	INSTALL (TARGETS ${FULL_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)	
ENDFUNCTION()

ADD_SGE_EXAMPLE(anim "sprite;systems;texture;time" "")
ADD_SGE_EXAMPLE(appdir "config" "")
ADD_SGE_EXAMPLE(asio_window "systems" "")
ADD_SGE_EXAMPLE(bitmapfont "fontbitmap;fonttext;systems" "")
ADD_SGE_EXAMPLE(caps "config" "")
ADD_SGE_EXAMPLE(cie "" "")
ADD_SGE_EXAMPLE(collision "sprite;systems;time" "")
ADD_SGE_EXAMPLE(console "console;systems" "")
ADD_SGE_EXAMPLE(configdir "config" "")
ADD_SGE_EXAMPLE(doppler "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(fullscreen "systems;time" "")
ADD_SGE_EXAMPLE(ini "parse" "")
ADD_SGE_EXAMPLE(input "systems" "")
ADD_SGE_EXAMPLE(intrusivesprite "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(json "parse" "")
ADD_SGE_EXAMPLE(mergeimage "systems" "")
#ADD_SGE_EXAMPLE(model "systems" "")
ADD_SGE_EXAMPLE(plugin "config" "")
ADD_SGE_EXAMPLE(pointsprite "systems;sprite;texture;time" "")
ADD_SGE_EXAMPLE(pool "systems;time" "")
ADD_SGE_EXAMPLE(savetexture "systems;sprite;texture;shader" "")
ADD_SGE_EXAMPLE(screenshot "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(shader/raw "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(spritecolor "sprite;systems" "")
ADD_SGE_EXAMPLE(sound "systems;time" "${Boost_PROGRAM_OPTIONS_LIBRARY}")
ADD_SGE_EXAMPLE(startprocess "process" "")
ADD_SGE_EXAMPLE(target "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(texture3d "systems;texture;camera;shader;time;config" "${Boost_PROGRAM_OPTIONS_LIBRARY}")
ADD_SGE_EXAMPLE(texture_filter "systems;sprite;texture;camera;time" "")
ADD_SGE_EXAMPLE(vertex "systems" "")
ADD_SGE_EXAMPLE(tutorial/font "fonttext;sprite;systems" "")
ADD_SGE_EXAMPLE(tutorial/sound_01 "config;systems" "")
ADD_SGE_EXAMPLE(tutorial/sound_02 "config;systems" "")
ADD_SGE_EXAMPLE(tutorial/sound_03 "config;systems;time" "")
ADD_SGE_EXAMPLE(tutorial/sprite_01 "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(tutorial/sprite_02 "sprite;systems;texture" "")
ADD_SGE_EXAMPLE(cg1/ex04 "systems;time" "")
