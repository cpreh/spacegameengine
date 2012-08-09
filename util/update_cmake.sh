#!/bin/bash

function die()
{
	exit -1
}

function update_cmake_file()
{
	local cmakefile="$1"

	update_cmake \
		"${cmakefile}" \
		"${@:2}" \
		|| die

	mv "${cmakefile}".new "${cmakefile}" || die

	chmod -x "${cmakefile}" || die
}

update_cmake_file \
	src/CMakeLists.txt \
	SGE_CORE_INCLUDE_FILES \
	-n \
	include/sge \
	-r \
	include/sge/error \
	src/include

update_cmake_file \
	src/CMakeLists.txt \
	SGE_CORE_SRC_FILES \
	-n \
	src

update_cmake_file \
	alda/src/CMakeLists.txt \
	ALDA_FILES \
	alda/src

function update_sublibrary()
{
	local sublibrary="$1"

	local upperpath=$(tr 'a-z' 'A-Z' <<< "${sublibrary}")

	update_cmake_file \
		src/"${sublibrary}"/CMakeLists.txt \
		SGE_"${upperpath////}"_FILES \
		"${@:2}" \
		include/sge/"${sublibrary}" \
		src/"${sublibrary}"
}

function update_plugin()
{
	local plugin="$1"
	local upperplugin=$(tr 'a-z' 'A-Z' <<< "${plugin}")

	update_cmake_file \
		src/plugins/"${plugin}"/CMakeLists.txt \
		SGE_"${upperplugin}"_FILES \
		src/plugins/"${plugin}"
}

# base libs
update_sublibrary audio

update_sublibrary camera

update_sublibrary cegui

# charconv
update_cmake_file \
	src/charconv/CMakeLists.txt \
	SGE_CHARCONV_BASE_FILES \
	include/sge/charconv \
	-n \
	src/charconv \
	src/charconv/include/sge/src/charconv

update_cmake_file \
	src/charconv/CMakeLists.txt \
	SGE_CHARCONV_ICONV_FILES \
	src/charconv/include/sge/src/charconv/backends/iconv \
	src/charconv/backends/iconv

update_cmake_file \
	src/charconv/CMakeLists.txt \
	SGE_CHARCONV_WINDOWS_FILES \
	src/charconv/include/sge/src/charconv/backends/windows \
	src/charconv/backends/windows

update_sublibrary bvh

update_sublibrary cg

update_sublibrary config

update_sublibrary console

update_sublibrary font \
	"include/sge/font/plugin" \
	"src/font/plugin" \
	"include/sge/font/weight" \
	"src/font/weight" \
	"-n"

update_sublibrary font/bitmap

update_sublibrary font/draw

update_sublibrary graph

update_sublibrary image

update_sublibrary image2d

update_sublibrary image3d

update_sublibrary input

update_sublibrary line_drawer

update_sublibrary log

update_sublibrary media

update_sublibrary model/md3

update_sublibrary model/obj

update_sublibrary opencl

update_sublibrary parse

update_sublibrary projectile

update_sublibrary plugin

function renderer_inc_src() {
	echo "include/sge/renderer/$1" "src/renderer/$1"
}

update_cmake_file \
	src/renderer/CMakeLists.txt \
	SGE_RENDERER_FILES \
	-n \
	include/sge/renderer \
	src/renderer \
	-r \
	src/renderer/include \
	$(renderer_inc_src caps) \
	$(renderer_inc_src clear) \
	$(renderer_inc_src color_buffer) \
	$(renderer_inc_src context) \
	$(renderer_inc_src display_mode) \
	$(renderer_inc_src index) \
	$(renderer_inc_src light) \
	$(renderer_inc_src lock_flags) \
	$(renderer_inc_src occlusion_query) \
	$(renderer_inc_src parameters) \
	$(renderer_inc_src pixel_format) \
	$(renderer_inc_src plugin) \
	$(renderer_inc_src projection) \
	$(renderer_inc_src state) \
	$(renderer_inc_src target) \
	$(renderer_inc_src texture) \
	$(renderer_inc_src vf)

update_sublibrary renderer/cg

update_sublibrary renderer/opengl

update_sublibrary resource_tree

update_sublibrary rucksack

update_sublibrary scenic

update_sublibrary shader

update_sublibrary sprite

update_sublibrary systems

update_sublibrary texture

update_sublibrary timer

update_sublibrary viewport

update_sublibrary window

function plugin_inc_src() {
	echo "src/plugins/$1/include/sge/$1/$2" "src/plugins/$1/src/$2"
}

function opengl_inc_src() {
	plugin_inc_src opengl "$1"
}

# plugins
update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_BASE_FILES \
	-n \
	src/plugins/opengl/src \
	src/plugins/opengl/include/sge/opengl \
	-r \
	$(opengl_inc_src buffer) \
	$(opengl_inc_src clear) \
	$(opengl_inc_src context) \
	$(opengl_inc_src convert) \
	$(opengl_inc_src device_state) \
	$(opengl_inc_src fbo) \
	$(opengl_inc_src glew) \
	$(opengl_inc_src light) \
	$(opengl_inc_src occlusion_query) \
	$(opengl_inc_src render_context) \
	$(opengl_inc_src state) \
	$(opengl_inc_src texture) \
	$(opengl_inc_src vf)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_WIN32_FILES \
	$(opengl_inc_src wgl) \
	$(opengl_inc_src windows)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_COCOA_FILES \
	-e '.*\.(mm|cpp)?' \
	$(opengl_inc_src cocoa)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_X11_FILES \
	$(opengl_inc_src glx) \
	$(opengl_inc_src x11)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_XRANDR_FILES \
	$(opengl_inc_src xrandr)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_CG_FILES \
	$(opengl_inc_src cg)

update_plugin audio_null

update_plugin devil

function d3d9_inc_src() {
	plugin_inc_src d3d9 "$1"
}

update_cmake_file \
	src/plugins/d3d9/CMakeLists.txt \
	SGE_D3D9_BASE_FILES \
	-n \
	src/plugins/d3d9/src \
	src/plugins/d3d9/include/sge/d3d9 \
	-r \
	src/plugins/d3d9/include/sge/d3d9/query \
	src/plugins/d3d9/include/sge/d3d9/swapchain \
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
	$(d3d9_inc_src vf)

update_cmake_file \
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

update_plugin x11input
