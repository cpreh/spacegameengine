function(
	path_to_enable_var
	OUT
	PATHVAR
)
	string(
		TOUPPER
		"${PATHVAR}"
		UPPER_RESULT
	)

	string(
		REPLACE
		"/"
		""
		UPPER_RESULT
		${UPPER_RESULT}
	)

	set(
		${OUT}
		ENABLE_${UPPER_RESULT}
		PARENT_SCOPE
	)
endfunction()

function(
	add_sge_lib
	LIBNAME
	DESCRIPTION
	DEFAULT
)
	path_to_enable_var(
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

function(
	add_sge_lib_depends
	LIBNAME
	DESCRIPTION
	DEFAULT
	DEPENDS
)
	foreach(
		DEP
		${DEPENDS}
	)
		path_to_enable_var(
			OUT_VAR
			${DEP}
		)

		if(
			NOT ${OUT_VAR}
		)
			set(
				DEFAULT
				FALSE
			)

			message(
				"${LIBNAME} is not built because ${DEP} couldn't be found"
			)
		endif()
	endforeach()

	add_sge_lib(
		${LIBNAME}
		${DESCRIPTION}
		${DEFAULT}
	)
endfunction()


add_subdirectory(
	bvh
)

find_package(
	Cg
)

##################################################
# Core libraries
##################################################

add_subdirectory(
	core
)

add_sge_lib(
	log
	"Build the log base library"
	ON
)

add_sge_lib(
	media
	"Build the media base library"
	ON
)

add_sge_lib(
	plugin
	"Build the plugin library"
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
	font
	"Build the font library"
	ON
)

add_sge_lib(
	image
	"Build the image library"
	ON
)

add_sge_lib(
	image/ds
	"Build the image depth stencil library"
	ON
)

add_sge_lib(
	imageds2d
	"Build the image depth stencil 2d library"
	ON
)

add_sge_lib(
	image/color
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
	parse/ini
	"Build the ini parse library"
	ON
)

add_sge_lib(
	parse/json
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
	model/md3
	"Build the md3 model library"
	ON
)

add_sge_lib(
	model/obj
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
	font/bitmap
	"Build the bitmap font library"
	ON
)

add_sge_lib(
	font/draw
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
	console/gfx
	"Build the console gfx library"
	ON
)

add_sge_lib(
	rucksack
	"Build the rucksack library"
	ON
)

add_sge_lib(
	rucksack/viewport
	"Build the rucksack viewport library"
	ON
)

add_sge_lib(
	systems
	"Build the systems library"
	ON
)

##################################################
# Libraries with Cg dependencies
##################################################

add_sge_lib_depends(
	shader
	"Build the shader wrapper library"
	ON
	"cg;renderer/cg"
)

add_sge_lib_depends(
	postprocessing
	"Build the postprocessing library"
	ON
	"cg;renderer/cg;shader"
)

add_sge_lib_depends(
	scenic
	"Build the scenic library"
	ON
	"cg;renderer/cg;shader"
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

add_sge_lib_depends(
	opencl
	"Build the opencl library"
	${OPENCL_FOUND}
	"renderer/opengl"
)

add_sge_lib(
	projectile
	"Build the projectile library"
	${BULLET_FOUND}
)

##################################################
# Plugins
##################################################

add_subdirectory(
	plugins
)
