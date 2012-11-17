include(
	AwlMainGenerator
)

function(
	add_sge_example_base
	EXAMPLE_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
	INCLUDE_DIRS
	CONSOLE_EXAMPLE
)
	sge_check_optional_deps(
		"The ${EXAMPLE_NAME} example"
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
		"sge_example_${FULL_NAME}"
	)

	set(
		SOURCE_FILE
		"${EXAMPLE_NAME}.cpp"
	)

	if(
		CONSOLE_EXAMPLE
	)
		add_executable(
			"${FULL_NAME}"
			${SOURCE_FILE}
		)
	else()
		awl_utils_add_portable_executable(
			${FULL_NAME}
			"example_main"
			${SOURCE_FILE}
		)

		target_link_libraries(
			${FULL_NAME}
			${awl_TARGET}
		)
	endif()

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

	sge_add_include_dirs(
		"${FULL_NAME}"
		"${INCLUDE_DIRS}"
	)

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

function(
	add_sge_example
	EXAMPLE_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
	INCLUDE_DIRS
)
	add_sge_example_base(
		"${EXAMPLE_NAME}"
		"${SGE_LIBRARIES}"
		"${ADDITIONAL_LIBRARIES}"
		"${INCLUDE_DIRS}"
		FALSE
	)
endfunction()

function(
	add_sge_console_example
	EXAMPLE_NAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
	INCLUDE_DIRS
)
	add_sge_example_base(
		"${EXAMPLE_NAME}"
		"${SGE_LIBRARIES}"
		"${ADDITIONAL_LIBRARIES}"
		"${INCLUDE_DIRS}"
		TRUE
	)
endfunction()

include_directories(
	"include"
)

add_definitions(
	${awl_DEFINITIONS}
)

find_package(
	Cg
)

add_sge_example(
	anaglyph
	"sgecamera;sgeconfig;sgeimage;sgeinput;sgelog;sgemodelmd3;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	app_path
	"sgeconfig"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	audio_minimal
	"sgeaudio;sgeconfig;sgeplugin"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	bitmapfont
	"sgeconfig;sgefont;sgefontbitmap;sgefontdraw;sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	caps
	"sgeconfig;sgeplugin;sgerenderer;sgewindow"
	"${fcppt_core_TARGET};${awl_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	color_string_convert
	"sgeimage"
	"${fcppt_core_TARGET}"
	""
)

add_sge_console_example(
	config
	"sgeconfig"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	console
	"sgeconfig;sgeconsole;sgefont;sgeimage;sgeinput;sgerenderer;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

#add_sge_example(
#	control_scheme
#	"sgeconfig;sgefont;sgefontdraw;sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
#	""
#)

message("Fix the cube map example!")

#add_sge_example(
#	cube_map
#	"sgecamera;sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow;sgeimage2d;sgeconfig;sgescenic"
#	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
#	"${Cg_INCLUDE_DIRS}"
#)

add_sge_example(
	display_mode
	"sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET}"
	""
)

add_sge_example(
	doppler
	"sgeaudio;sgeconfig;sgeinput;sgelog;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	font
	"sgefont;sgefontdraw;sgeimage;sgerenderer;sgesystems;sgeviewport;sgewindow"
	""
	""
)

add_sge_example(
	fullscreen
	"sgeimage;sgelog;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	graph
	"sgegraph;sgeimage;sgelog;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	ini
	"sgeparse"
	"${fcppt_core_TARGET}"
	""
)

add_sge_example(
	input
	"sgeinput;sgelog;sgesystems;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	intrusivesprite
	"sgeconfig;sgeinput;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	json
	"sgeparse"
	"${fcppt_core_TARGET}"
	""
)

add_sge_example(
	line_drawer
	"sgefont;sgefontdraw;sgeimage;sgeinput;sgeline_drawer;sgerenderer;sgesystems;sgetimer;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_sge_example(
		linux_stats
		"sgefont;sgefontdraw;sgegraph;sgelog;sgerenderer;sgesystems;sgeviewport;sgewindow;sgeimage;sgetimer"
		"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
		""
	)
endif()

add_sge_console_example(
	mergeimage
	"sgecore;sgeimage;sgeimage2d;sgesystems"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	multi_texture
	"sgeconfig;sgeimage;sgeinput;sgemedia;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	multi_texture_sprite
	"sgeconfig;sgeinput;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	noise
	"sgeimage;sgeimage2d;sgelog;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

#add_sge_example(
#	occlusion_query
#	"sgecamera;sgeconfig;sgefont;sgefontdraw;sgeimage;sgeinput;sgelog;sgemedia;sgescenic;sgerenderer;sgesystems;sgetimer;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
#	"${Cg_INCLUDE_DIRS}"
#)

add_sge_console_example(
	opengl
	"sgerenderer;sgerendereropengl;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	ortho_view
	"sgecamera;sgeconfig;sgeimage;sgeinput;sgelog;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	plugin
	"sgeaudio;sgeconfig;sgefont;sgeimage2d;sgeinput;sgelog;sgeplugin;sgerenderer"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

message("Fix the point sprite example!")

#add_sge_example(
#	pointsprite
#	"sgeconfig;sgeinput;sgelog;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES};${Boost_PROGRAM_OPTIONS_LIBRARIES}"
#	""
#)

add_sge_example(
	projectile/main
	"sgeimage;sgeinput;sgelog;sgeprojectile;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

message("Fix the save texture example!")

#add_sge_example(
#	savetexture
#	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgemedia;sgerenderer;sgeshader;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
#)

add_sge_console_example(
	raw_view
	""
	"${fcppt_core_TARGET}"
	""
)

add_sge_console_example(
	resource_tree
	"sgeconfig;sgeresource_tree"
	"${fcppt_core_TARGET};${fcppt_filesystem_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	scenic
	"sgeconfig;sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow;sgescenic;sgecamera;sgegraph;sgeparse"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES};${Boost_CHRONO_LIBRARIES};${Boost_PROGRAM_OPTIONS_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	screenshot
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

message("Fix the shader cube example!")

#add_sge_example(
#	shader/cube
#	"sgecamera;sgeconfig;sgefonttext;sgeimage;sgeimage2d;sgeinput;sgelog;sgerenderer;sgeshader;sgesystems;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
#)

message("Fix the shader raw example!")

#add_sge_example(
#	shader/raw
#	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgelog;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
#)

add_sge_console_example(
	sound
	"sgeaudio;sgeconfig;sgelog;sgesystems"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	spritecolor
	"sgeimage;sgeinput;sgelog;sgerenderer;sgesprite;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	stencil
	"sgeconfig;sgeimage;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	swoosh
	"sgeaudio;sgeconfig;sgeinput;sgelog;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow;sgegraph"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	target
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	texture_filter
	"sgecamera;sgefont;sgefontdraw;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgetimer;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	tutorial/sound_01
	"sgeaudio;sgeconfig;sgesystems"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_console_example(
	tutorial/sound_02
	"sgeaudio;sgeconfig;sgesystems"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	tutorial/sprite_02
	"sgeconfig;sgeimage;sgeimage2d;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	tutorial/sprite_03
	"sgeconfig;sgeimage;sgeinput;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	vertex
	"sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	vertex_index
	"sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	vertex_planar
	"sgeimage;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	vertex_texture
	"sgeconfig;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	volume_texture
	"sgecamera;sgeimage;sgeimage3d;sgeinput;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_sge_example(
	window_without_input
	"sgeimage;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	""
)

add_subdirectory(
	bvh
)

add_subdirectory(
	gui
)

add_subdirectory(
	cg
)

add_subdirectory(
	opencl
)

add_subdirectory(
	rucksack
)
