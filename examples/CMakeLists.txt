function(
	ADD_SGE_EXAMPLE
	EXAMPLE_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
)
	foreach(
		SGELIB
		${SGE_LIBRARIES}
	)
		string(
			REPLACE
			"sge"
			""
			SGELIB_SUFFIX
			${SGELIB}
		)

		string(
			TOUPPER
			${SGELIB_SUFFIX}
			SGELIB_UPPER
		)

		if(
			NOT ENABLE_${SGELIB_UPPER}
		)
			message(
				STATUS
				"${EXAMPLE_NAME} example will not be built because ${SGELIB} is not enabled!"
			)

			return()
		endif()
	endforeach()

	string(
		REPLACE
		"/"
		""
		FULL_NAME
		${EXAMPLE_NAME}
	)

	set(
		FULL_NAME
		sge${FULL_NAME}example
	)

	add_executable(
		${FULL_NAME}
		${EXAMPLE_NAME}.cpp
	)

	transform_sge_link_targets(
		"${SGE_LIBRARIES}"
	)

	if(
		SGE_DEFAULT_LINK_STATIC
	)
		sge_set_static_flags(
			${FULL_NAME}
		)
	endif()

	target_link_libraries(
		${FULL_NAME}
		${ADDITIONAL_LIBRARIES}
		${SGELIBS_TARGETS_RESULT}
	)

	install(
		TARGETS
		${FULL_NAME}
		DESTINATION
		${INSTALL_BINARY_DIR}
	)
endfunction()

add_definitions(
	${Awl_DEFINITIONS}
)

ADD_SGE_EXAMPLE(anaglyph "sgeconfig;sgesystems;sgetexture;sgemodelmd3;sgeshader;sgecamera" "")
ADD_SGE_EXAMPLE(app_path "sgeconfig" "")
ADD_SGE_EXAMPLE(asio_window "sgesystems" "${Awl_LIBRARIES}")
ADD_SGE_EXAMPLE(audio_minimal "sgeconfig;sgesystems;sgeaudio" "")
ADD_SGE_EXAMPLE(bitmapfont "sgefontbitmap;sgefonttext;sgesystems" "")
ADD_SGE_EXAMPLE(caps "sgeconfig;sgeplugin;sgerenderer;sgewindow" "${Awl_LIBRARIES}")
ADD_SGE_EXAMPLE(console "sgeconsole;sgefonttext;sgeinput;sgesystems" "")
ADD_SGE_EXAMPLE(config_path "sgeconfig" "")
ADD_SGE_EXAMPLE(doppler "sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(fullscreen "sgesystems" "")
ADD_SGE_EXAMPLE(ini "sgeparse" "")
ADD_SGE_EXAMPLE(input "sgesystems" "")
ADD_SGE_EXAMPLE(intrusivesprite "sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(json "sgeparse" "")
ADD_SGE_EXAMPLE(line_drawer "sgeline_drawer;sgeconfig;sgefonttext;sgesystems" "")
ADD_SGE_EXAMPLE(mergeimage "sgesystems" "")
ADD_SGE_EXAMPLE(model_loader "sgeconfig;sgesystems;sgetexture;sgemodelobj;sgecamera;sgeparse;sgeline_drawer" "")
ADD_SGE_EXAMPLE(multi_texture "sgeconfig;sgesystems" "")
ADD_SGE_EXAMPLE(multi_texture_sprite "sgeconfig;sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(opengl "sgerenderer;sgerendereropengl;sgeviewport;sgesystems" "")
ADD_SGE_EXAMPLE(ortho_view "sgesprite;sgesystems;sgetexture;sgecamera" "")
ADD_SGE_EXAMPLE(plugin "sgeaudio;sgeconfig;sgefont;sgeimage2d;sgeinput;sgerenderer" "")
ADD_SGE_EXAMPLE(pointsprite "sgesystems;sgesprite;sgetexture" "")
ADD_SGE_EXAMPLE(savetexture "sgesystems;sgesprite;sgetexture;sgeshader" "")
ADD_SGE_EXAMPLE(screenshot "sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(shader/cube "sgeshader;sgecamera;sgesystems;sgefonttext;sgeconfig;" "")
ADD_SGE_EXAMPLE(shader/raw "sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(spritecolor "sgesprite;sgesystems" "")
ADD_SGE_EXAMPLE(sound "sgesystems" "")
ADD_SGE_EXAMPLE(stencil "sgeconfig;sgesprite;sgesystems;sgetexture;sgeviewport" "")
ADD_SGE_EXAMPLE(target "sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(texture_filter "sgecamera;sgeconfig;sgefonttext;sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(vertex "sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow" "")
ADD_SGE_EXAMPLE(vertex_index "sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow" "")
ADD_SGE_EXAMPLE(vertex_planar "sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow" "")
ADD_SGE_EXAMPLE(vertex_texture "sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow" "")
ADD_SGE_EXAMPLE(volume_texture "sgecamera;sgeimage3d;sgesystems" "")
ADD_SGE_EXAMPLE(tutorial/font "sgefonttext;sgesprite;sgesystems" "")
ADD_SGE_EXAMPLE(tutorial/sound_01 "sgeconfig;sgesystems" "")
ADD_SGE_EXAMPLE(tutorial/sound_02 "sgeconfig;sgesystems" "")
ADD_SGE_EXAMPLE(tutorial/sprite_01 "sgesprite;sgesystems;sgetexture" "")
ADD_SGE_EXAMPLE(tutorial/sprite_02 "sgesprite;sgesystems;sgetexture" "")

IF(ENABLE_CEGUI)
	ADD_SUBDIRECTORY(gui)
ENDIF()

IF(ENABLE_PROJECTILE)
	ADD_SUBDIRECTORY(projectile)
ENDIF()

IF(ENABLE_OPENCL)
	ADD_SUBDIRECTORY(opencl)
ENDIF()
