#!/bin/bash

set -e -u

function update_sublibrary()
{
	local libdir=libs/"$1"

	update_cmake.sh \
		"${libdir}"/files.txt \
		"${libdir}"
}

function update_plugin()
{
	local plugindir=plugins/"$1"

	update_cmake.sh \
		"${plugindir}"/files.txt \
		"${plugindir}"
}

function update_example_library()
{
	local exampledir=examples/"$1"

	update_cmake.sh \
		"${exampledir}"/files.txt \
		"${exampledir}"
}

function update_tool()
{
	local tooldir=tools/"$1"

	update_cmake.sh \
		"${tooldir}/files.txt" \
		"${tooldir}"
}

# base libs
declare -a BASE_LIBS

BASE_LIBS=(
	audio
	bresenham
	bvh
	camera
	charconv
	core
	cg
	config
	console
	consolegfx
	cursor
	font
	fontbitmap
	fontdraw
	gui
	graph
	image
	image2d
	image3d
	imagecolor
	imageds
	imageds2d
	input
	line_drawer
	log
	media
	modelmd3
	modelobj
	noise
	opencl
	parse
	parseini
	parsejson
	postprocessing
	projectile
	plugin
	renderer
	renderercg
	rendereropengl
	resource_tree
	rucksack
	rucksackviewport
	scenic
	shader
	sprite
	systems
	texture
	timer
	viewport
	window
)

for lib in ${BASE_LIBS[@]} ; do
	update_sublibrary ${lib}
done

declare -a PLUGINS

PLUGINS=(
	audio_null
	dinput
	evdev
	gdifont
	libpng
	openal
	pango
	sdlinput
	vorbis
	wave
	wininput
	wlinput
	x11input
)

for plugin in ${PLUGINS[@]} ; do
	update_plugin ${plugin}
done

declare -a OPENGL_BACKENDS

update_cmake.sh \
	plugins/opengl/files.txt \
	plugins/opengl/include \
	plugins/opengl/src

function update_opengl() {
	local backend_dir=plugins/opengl/backends/"$1"

	update_cmake.sh \
		"${backend_dir}"/files.txt \
		"${backend_dir}"
}

OPENGL_BACKENDS=(
	cg
	egl
	egl_x11
	glx
	sdl
	wayland
	windows
	x11
	xrandr
)

for backend in ${OPENGL_BACKENDS[@]} ; do
	update_opengl ${backend}
done

update_cmake.sh \
	plugins/d3d9/files.txt \
	plugins/d3d9/include \
	plugins/d3d9/src

update_cmake.sh \
	plugins/d3d9/cg/files.txt \
	plugins/d3d9/cg

update_example_library rucksack/testbed

update_tool control_config

update_cmake.sh \
	doc/files.txt \
    doc

update_cmake.sh \
	doc/libs_files.txt \
    libs
