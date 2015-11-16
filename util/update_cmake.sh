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

	update_cmake \
		src/"${sublibrary}"/CMakeLists.txt \
		SGE_"${upperpath/\//}"_FILES \
		"${@:2}" \
		include/sge/"${sublibrary}" \
		src/"${sublibrary}"
}

function update_plugin()
{
	local plugin="$1"
	local upperplugin=$(toupper "${plugin}")

	update_cmake \
		src/plugins/"${plugin}"/CMakeLists.txt \
		SGE_"${upperplugin}"_FILES \
		src/plugins/"${plugin}"
}

function update_example_library()
{
	local examplelibrary="$1"

	local upperpath=$(toupper "${examplelibrary}")

	local prefix=examples/"${examplelibrary}"

	update_cmake \
		"${prefix}"/CMakeLists.txt \
		SGE_"${upperpath/\//}"_FILES \
		"${@:2}" \
		"${prefix}"/include/sge/"${examplelibrary}" \
		"${prefix}"/src
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

update_sublibrary console \
	"include/sge/console/callback" \
	"src/console/callback" \
	"-n"

update_sublibrary console/gfx

update_sublibrary font \
	"include/sge/font/align_h" \
	"src/font/align_h" \
	"include/sge/font/plugin" \
	"src/font/plugin" \
	"include/sge/font/weight" \
	"src/font/weight" \
	"-n"

update_sublibrary font/bitmap

update_sublibrary font/draw

update_sublibrary gui

update_sublibrary graph

update_sublibrary image \
	"include/sge/image/algorithm" \
	"include/sge/image/traits" \
	"include/sge/image/view" \
	"src/image/include" \
	"src/image/algorithm" \
	"-n"

update_sublibrary image2d

update_sublibrary image3d

update_sublibrary image/color

update_sublibrary image/ds

update_sublibrary imageds2d

update_sublibrary input

update_sublibrary line_drawer

update_sublibrary log

update_sublibrary media

update_sublibrary model/md3

update_sublibrary model/obj

update_sublibrary opencl

update_sublibrary parse \
	"src/parse/include" \
	"-n"

update_sublibrary parse/ini

update_sublibrary parse/json

update_sublibrary postprocessing

update_sublibrary projectile

update_sublibrary plugin

function renderer_inc_src() {
	echo "include/sge/renderer/$1" "src/renderer/$1"
}

update_cmake \
	src/renderer/CMakeLists.txt \
	SGE_RENDERER_FILES \
	-n \
	include/sge/renderer \
	src/renderer \
	-r \
	src/renderer/include \
	include/sge/renderer/buffer \
	$(renderer_inc_src caps) \
	$(renderer_inc_src clear) \
	$(renderer_inc_src color_buffer) \
	$(renderer_inc_src context) \
	$(renderer_inc_src depth_stencil_buffer) \
	$(renderer_inc_src device) \
	$(renderer_inc_src display_mode) \
	$(renderer_inc_src index) \
	$(renderer_inc_src lock_flags) \
	$(renderer_inc_src occlusion_query) \
	$(renderer_inc_src pixel_format) \
	$(renderer_inc_src plugin) \
	$(renderer_inc_src projection) \
	$(renderer_inc_src state) \
	$(renderer_inc_src target) \
	$(renderer_inc_src texture) \
	$(renderer_inc_src vertex) \
	$(renderer_inc_src vf)

update_sublibrary renderer/cg

update_sublibrary renderer/opengl

update_sublibrary resource_tree

update_cmake \
	src/rucksack/CMakeLists.txt \
	SGE_RUCKSACK_FILES \
	-n \
	include/sge/rucksack \
	src/rucksack \
	-r \
	src/rucksack/include \
	include/sge/rucksack/widget \
	src/rucksack/widget

update_sublibrary rucksack/viewport

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
	echo "src/plugins/$1/include/sge/$1/$2" "src/plugins/$1/src/$2"
}

function opengl_inc_src() {
	plugin_inc_src opengl "$1"
}

function update_opengl() {
	update_cmake \
		src/plugins/opengl/CMakeLists.txt \
		"$@"
}

update_cmake \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_BASE_FILES \
	-n \
	src/plugins/opengl/src \
	src/plugins/opengl/include/sge/opengl \
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
	$(opengl_inc_src texture) \
	$(opengl_inc_src vertex) \
	$(opengl_inc_src vf)

update_opengl \
	SGE_OPENGL_WIN32_FILES \
	$(opengl_inc_src wgl) \
	$(opengl_inc_src windows)

update_opengl \
	SGE_OPENGL_COCOA_FILES \
	-e '.*\.(mm|cpp)?' \
	$(opengl_inc_src cocoa)

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

update_plugin audio_null

function d3d9_inc_src() {
	plugin_inc_src d3d9 "$1"
}

update_cmake \
	src/plugins/d3d9/CMakeLists.txt \
	SGE_D3D9_BASE_FILES \
	-n \
	src/plugins/d3d9/src \
	src/plugins/d3d9/include/sge/d3d9 \
	-r \
	src/plugins/d3d9/include/sge/d3d9/query \
	src/plugins/d3d9/include/sge/d3d9/swapchain \
	src/plugins/d3d9/include/sge/d3d9/volume \
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
	src/plugins/d3d9/CMakeLists.txt \
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

update_plugin wininput

update_plugin x11input

update_example_library rucksack/testbed


update_tool control_config


update_cmake \
	doc/CMakeLists.txt \
	SGE_DOC_FILES \
	include \
	-e '.*' \
	doc
