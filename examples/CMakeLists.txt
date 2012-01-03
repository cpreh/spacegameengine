function(
	ADD_SGE_EXAMPLE
	EXAMPLE_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
)
	sge_check_optional_deps(
		"${EXAMPLE_NAME}"
		"${SGE_LIBRARIES}"
	)

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

add_sge_example(
	anaglyph
	"sgecamera;sgeconfig;sgeimage;sgeinput;sgelog;sgemodelmd3;sgerenderer;sgeshader;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	app_path
	"sgeconfig"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	asio_window
	"sgeinput;sgesystems;sgewindow"
	"${Fcppt_core_LIBRARIES};${Awl_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	audio_minimal
	"sgeaudio;sgeconfig;sgeplugin"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	bitmapfont
	"sgeconfig;sgefontbitmap;sgefonttext;sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	caps
	"sgeconfig;sgeplugin;sgerenderer;sgewindow"
	"${Fcppt_core_LIBRARIES};${Awl_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	config_path
	"sgeconfig"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	console
	"sgeconfig;sgeconsole;sgefonttext;sgeimage;sgeinput;sgerenderer;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	doppler
	"sgeaudio;sgeconfig;sgeinput;sgelog;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	fullscreen
	"sgeimage;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	ini
	"sgeparse"
	"${Fcppt_core_LIBRARIES}"
)

add_sge_example(
	input
	"sgeinput;sgelog;sgesystems;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	intrusivesprite
	"sgeconfig;sgeinput;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	json
	"sgeparse"
	"${Fcppt_core_LIBRARIES}"
)

add_sge_example(
	line_drawer
	"sgeconfig;sgefonttext;sgeimage;sgeinput;sgeline_drawer;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	mergeimage
	"sgecore;sgeimage;sgeimage2d;sgesystems"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	model_loader
	"sgecamera;sgeconfig;sgeimage;sgeinput;sgeline_drawer;sgelog;sgemedia;sgemodelobj;sgeparse;sgerenderer;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	multi_texture
	"sgeconfig;sgeimage;sgeinput;sgemedia;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	multi_texture_sprite
	"sgeconfig;sgeinput;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	opengl
	"sgerenderer;sgerendereropengl;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	ortho_view
	"sgecamera;sgeconfig;sgeimage;sgeinput;sgelog;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	plugin
	"sgeaudio;sgeconfig;sgefont;sgeimage2d;sgeinput;sgelog;sgeplugin;sgerenderer"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	pointsprite
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgemedia;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	projectile/main
	"sgeimage;sgeinput;sgelog;sgeprojectile;sgerenderer;sgesprite;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	savetexture
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgemedia;sgerenderer;sgeshader;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	screenshot
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	shader/cube
	"sgecamera;sgeconfig;sgefonttext;sgeimage;sgeimage2d;sgeinput;sgelog;sgerenderer;sgeshader;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	shader/raw
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgelog;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	sound
	"sgeaudio;sgeconfig;sgelog;sgesystems"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	spritecolor
	"sgeimage;sgeinput;sgelog;sgerenderer;sgesprite;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	stencil
	"sgeconfig;sgeimage;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	target
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	texture_filter
	"sgecamera;sgeconfig;sgefonttext;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	tutorial/font
	"sgeconfig;sgefonttext;sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	tutorial/sound_01
	"sgeaudio;sgeconfig;sgesystems"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	tutorial/sound_02
	"sgeaudio;sgeconfig;sgesystems"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	tutorial/sprite_01
	"sgeconfig;sgeimage2d;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	tutorial/sprite_02
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	vertex
	"sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	vertex_index
	"sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	vertex_planar
	"sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	vertex_texture
	"sgeconfig;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

add_sge_example(
	volume_texture
	"sgecamera;sgeimage;sgeimage3d;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Fcppt_filesystem_LIBRARIES}"
)

if(
	ENABLE_CEGUI
)
	add_subdirectory(
		gui
	)
endif()

if(
	ENABLE_OPENCL
)
	add_subdirectory(
		opencl
	)
endif()
