include(
	CMakeParseArguments
)

function(
	add_sge_lib
	LIBNAME
	DESCRIPTION
	DEFAULT
)

	set(
		MULTI_ARGS
		DEPENDS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	foreach(
		DEP
		${_DEPENDS}
	)
		libname_to_enable_var(
			ENABLE_VAR
			${DEP}
		)

		sge_check_enable_var(
			DEP_PRESENT
			${ENABLE_VAR}
		)

		if(
			NOT ${DEP_PRESENT}
		)
			set(
				DEFAULT
				FALSE
			)

			message(
				"${LIBNAME} is not built because ${ENABLE_VAR}=OFF"
			)
		endif()
	endforeach()

	libname_to_enable_var(
		ENABLE_VAR
		${LIBNAME}
	)

	option(
		${ENABLE_VAR}
		"${DESCRIPTION}"
		${DEFAULT}
	)

	if(
		${ENABLE_VAR}
	)
		add_subdirectory(
			${LIBNAME}
		)
	endif()
endfunction()


find_package(
	Cg
)

find_package(
	OpenGL
)

##################################################
# Core libraries
##################################################

add_subdirectory(
	core
)

add_sge_lib(
	bvh
	"Build the bvh library"
	ON
)

add_sge_lib(
	noise
	"Build the noise library"
	ON
)

add_sge_lib(
	log
	"Build the log base library"
	ON
)

add_sge_lib(
	plugin
	"Build the plugin library"
	ON
)

add_sge_lib(
	media
	"Build the media base library"
	ON
)

add_sge_lib(
	audio
	"Build the audio library"
	ON
)

add_sge_lib(
	charconv
	"Build the charconv library"
	ON
)

add_sge_lib(
	image
	"Build the image library"
	ON
)

add_sge_lib(
	imageds
	"Build the image depth stencil library"
	ON
)

add_sge_lib(
	imageds2d
	"Build the image depth stencil 2d library"
	ON
)

add_sge_lib(
	imagecolor
	"Build the imagecolor library"
	ON
)

add_sge_lib(
	image2d
	"Build the image2d library"
	ON
)

add_sge_lib(
	image3d
	"Build the image3d library"
	ON
)

add_sge_lib(
	font
	"Build the font library"
	ON
)

add_sge_lib(
	window
	"Build the window library"
	ON
)

add_sge_lib(
	input
	"Build the input library"
	ON
)

# Needs to be added before renderer
add_sge_lib(
	cg
	"Build the Cg library"
	${CG_FOUND}
)

add_sge_lib(
	renderer
	"Build the renderer library"
	ON
)

add_sge_lib(
	renderercg
	"Build the renderer cg frontend"
	${ENABLE_CG}
)

add_sge_lib(
	rendereropengl
	"Build the opengl renderer frontend"
	${OPENGL_FOUND}
)

##################################################
# Support libraries with simple dependencies
##################################################

add_sge_lib(
	config
	"Build the config library"
	ON
)

add_sge_lib(
	parse
	"Build the parse library"
	ON
)

add_sge_lib(
	parseini
	"Build the ini parse library"
	ON
)

add_sge_lib(
	parsejson
	"Build the json parse library"
	ON
)

add_sge_lib(
	timer
	"Build the timer library"
	ON
)

add_sge_lib(
	resource_tree
	"Build the resource tree library"
	ON
)

##################################################
# Support libraries with advanced dependencies
##################################################

add_sge_lib(
	texture
	"Build the texture helpers"
	ON
)

add_sge_lib(
	sprite
	"Build the sprite library"
	ON
)

add_sge_lib(
	graph
	"Build the graph library"
	ON
)

add_sge_lib(
	modelmd3
	"Build the md3 model library"
	ON
)

add_sge_lib(
	modelobj
	"Build the md3 model library"
	ON
)

add_sge_lib(
	viewport
	"Build the viewport library"
	ON
)

add_sge_lib(
	line_drawer
	"Build the line drawing library"
	ON
)

add_sge_lib(
	fontbitmap
	"Build the bitmap font library"
	ON
)

add_sge_lib(
	fontdraw
	"Build the font drawing library"
	ON
)

add_sge_lib(
	camera
	"Build the camera library"
	ON
)

add_sge_lib(
	console
	"Build the console library"
	ON
)

add_sge_lib(
	consolegfx
	"Build the console gfx library"
	ON
)

add_sge_lib(
	rucksack
	"Build the rucksack library"
	ON
)

add_sge_lib(
	rucksackviewport
	"Build the rucksack viewport library"
	ON
)

add_sge_lib(
	systems
	"Build the systems library"
	ON
)

add_sge_lib(
	gui
	"Build the gui library"
	ON
)

##################################################
# Libraries with Cg dependencies
##################################################

add_sge_lib(
	shader
	"Build the shader wrapper library"
	ON
	DEPENS
		cg
		renderercg
)

add_sge_lib(
	postprocessing
	"Build the postprocessing library"
	ON
	DEPENDS
		cg
		renderercg
		shader
)

add_sge_lib(
	scenic
	"Build the scenic library"
	ON
	DEPENDS
		cg
		renderercg
		shader
)

##################################################
# Libraries with external dependencies
##################################################

find_package(
	Bullet
)

find_package(
	CEGUI
)

find_package(
	OpenCL
)

add_sge_lib(
	cegui
	"Build the cegui subsystem"
	${CEGUI_FOUND}
)

add_sge_lib(
	opencl
	"Build the opencl library"
	${OpenCL_FOUND}
	DEPENDS
		rendereropengl
)

add_sge_lib(
	projectile
	"Build the projectile library"
	${BULLET_FOUND}
)
