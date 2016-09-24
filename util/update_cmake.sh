#!/bin/bash

set -e -u

function toupper()
{
	echo $(tr 'a-z' 'A-Z' <<< "$1")
}

function update_sublibrary()
{
	local sublibrary="$1"
	local upperpath=$(toupper "${sublibrary}")
	local libdir=libs/"${sublibrary}"

	update_cmake \
		"${libdir}"/CMakeLists.txt \
		SGE_"${upperpath}"_FILES \
		"${@:2}" \
		"${libdir}"
}

function update_plugin()
{
	local plugin="$1"
	local upperplugin=$(toupper "${plugin}")
	local plugindir=plugins/"${plugin}"

	update_cmake \
		"${plugindir}"/CMakeLists.txt \
		SGE_"${upperplugin}"_FILES \
		"${plugindir}"
}

function update_example_library()
{
	local examplelibrary="$1"
	local upperpath=$(toupper "${examplelibrary}")
	local exampledir=examples/"${examplelibrary}"

	update_cmake \
		"${exampledir}"/CMakeLists.txt \
		SGE_"${upperpath/\//}"_FILES \
		"${@:2}" \
		"${exampledir}"
}

function update_tool()
{
	local tool="$1"
	local tooldir="tools/${tool}"
	local uppertool="$(toupper "${tool}")"

	update_cmake \
		"${tooldir}/CMakeLists.txt" \
		"SGE_TOOL_${uppertool}_FILES" \
		"${tooldir}/include" \
		"${tooldir}/src"
}

# base libs
update_sublibrary audio

update_sublibrary camera

update_sublibrary cegui

update_sublibrary charconv

update_sublibrary core

update_sublibrary bvh

update_sublibrary cg

update_sublibrary config

update_sublibrary console

update_sublibrary consolegfx

update_sublibrary font

update_sublibrary fontbitmap

update_sublibrary fontdraw

update_sublibrary gui

update_sublibrary graph

update_sublibrary image

update_sublibrary image2d

update_sublibrary image3d

update_sublibrary imagecolor

update_sublibrary imageds

update_sublibrary imageds2d

update_sublibrary input

update_sublibrary line_drawer

update_sublibrary log

update_sublibrary media

update_sublibrary modelmd3

update_sublibrary modelobj

update_sublibrary noise

update_sublibrary opencl

update_sublibrary parse

update_sublibrary parseini

update_sublibrary parsejson

update_sublibrary postprocessing

update_sublibrary projectile

update_sublibrary plugin

update_sublibrary renderer

update_sublibrary renderercg

update_sublibrary rendereropengl

update_sublibrary resource_tree

update_sublibrary rucksack

update_sublibrary rucksackviewport

update_sublibrary scenic

update_sublibrary shader

update_sublibrary sprite

update_sublibrary systems

update_sublibrary texture

update_sublibrary timer

update_sublibrary viewport

update_sublibrary window

# plugins

function plugin_inc_src() {
	echo "plugins/$1/include/sge/$1/$2" "plugins/$1/src/$2"
}

function opengl_inc_src() {
	plugin_inc_src opengl "$1"
}

function update_opengl() {
	update_cmake \
		plugins/opengl/CMakeLists.txt \
		"$@"
}

update_cmake \
	plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_BASE_FILES \
	-n \
	plugins/opengl/src \
	plugins/opengl/include/sge/opengl \
	-r \
	$(opengl_inc_src backend) \
	$(opengl_inc_src buffer) \
	$(opengl_inc_src clear) \
	$(opengl_inc_src context) \
	$(opengl_inc_src convert) \
	$(opengl_inc_src fbo) \
	$(opengl_inc_src index) \
	$(opengl_inc_src info) \
	$(opengl_inc_src occlusion_query) \
	$(opengl_inc_src platform) \
	$(opengl_inc_src render_context) \
	$(opengl_inc_src state) \
	$(opengl_inc_src target) \
	$(opengl_inc_src texture) \
	$(opengl_inc_src vertex) \
	$(opengl_inc_src vf)

update_opengl \
	SGE_OPENGL_WIN32_FILES \
	$(opengl_inc_src wgl) \
	$(opengl_inc_src windows)

update_opengl \
	SGE_OPENGL_WAYLAND_FILES \
	$(opengl_inc_src wayland)

update_opengl \
	SGE_OPENGL_X11_FILES \
	$(opengl_inc_src x11)

update_opengl \
	SGE_OPENGL_GLX_FILES \
	$(opengl_inc_src glx) \

update_opengl \
	SGE_OPENGL_XRANDR_FILES \
	$(opengl_inc_src xrandr)

update_opengl \
	SGE_OPENGL_CG_FILES \
	$(opengl_inc_src cg)

update_opengl \
	SGE_OPENGL_EGL_FILES \
	-n \
	$(opengl_inc_src egl) \
	$(opengl_inc_src egl/visual) \

update_opengl \
	SGE_OPENGL_EGL_X11_FILES \
	$(opengl_inc_src egl/x11)

update_opengl \
	SGE_OPENGL_EGL_WAYLAND_FILES \
	$(opengl_inc_src egl/wayland)

update_plugin audio_null

function d3d9_inc_src() {
	plugin_inc_src d3d9 "$1"
}

update_cmake \
	plugins/d3d9/CMakeLists.txt \
	SGE_D3D9_BASE_FILES \
	-n \
	plugins/d3d9/src \
	plugins/d3d9/include/sge/d3d9 \
	-r \
	plugins/d3d9/include/sge/d3d9/query \
	plugins/d3d9/include/sge/d3d9/swapchain \
	plugins/d3d9/include/sge/d3d9/volume \
	$(d3d9_inc_src com) \
	$(d3d9_inc_src convert) \
	$(d3d9_inc_src devicefuncs) \
	$(d3d9_inc_src occlusion_query) \
	$(d3d9_inc_src parameters) \
	$(d3d9_inc_src queryfuncs) \
	$(d3d9_inc_src render_context) \
	$(d3d9_inc_src state) \
	$(d3d9_inc_src surface) \
	$(d3d9_inc_src surfacefuncs) \
	$(d3d9_inc_src swapchainfuncs) \
	$(d3d9_inc_src systemfuncs) \
	$(d3d9_inc_src target) \
	$(d3d9_inc_src texture) \
	$(d3d9_inc_src texturefuncs) \
	$(d3d9_inc_src vertex) \
	$(d3d9_inc_src vf) \
	$(d3d9_inc_src volumefuncs)

update_cmake \
	plugins/d3d9/CMakeLists.txt \
	SGE_D3D9_CG_FILES \
	$(d3d9_inc_src cg)

update_plugin dinput

update_plugin evdev

update_plugin gdifont

update_plugin libpng

update_plugin openal

update_plugin pango

update_plugin vorbis

update_plugin wave

update_plugin wic

update_plugin wininput

update_plugin wlinput

update_plugin x11input

update_example_library rucksack/testbed


update_tool control_config

# FIXME
#update_cmake \
#	doc/CMakeLists.txt \
#	SGE_DOC_FILES \
#	include \
#	-e '.*' \
#	doc
