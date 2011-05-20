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
	include/sge/audio \
	include/sge/charconv \
	include/sge/error \
	-n \
	include/sge/font \
	-r \
	include/sge/image \
	include/sge/image2d \
	include/sge/image3d \
	include/sge/input \
	include/sge/log \
	include/sge/model \
	include/sge/plugin \
	include/sge/renderer \
	include/sge/window

update_cmake_file \
	src/CMakeLists.txt \
	SGE_CORE_SRC_FILES \
	-n \
	src \
	-r \
	src/audio \
	src/charconv \
	-n \
	src/font \
	-r \
	src/image \
	src/image2d \
	src/image3d \
	src/input \
	src/log \
	src/model \
	src/plugin \
	src/renderer \
	src/window

function update_sublibrary()
{
	local sublibrary="$1"

	local upperpath="${sublibrary^^}"

	update_cmake_file \
		src/"${sublibrary}"/CMakeLists.txt \
		SGE_"${upperpath////}"_FILES \
		include/sge/"${sublibrary}" \
		src/"${sublibrary}"
}

function update_plugin()
{
	local plugin="$1"

	update_cmake_file \
		src/plugins/"${plugin}"/CMakeLists.txt \
		SGE_"${plugin^^}"_FILES \
		src/plugins/"${plugin}"
}

# base libs
update_sublibrary projectile

update_sublibrary cegui

update_sublibrary camera

update_sublibrary config

update_sublibrary console

update_sublibrary font/bitmap

update_sublibrary font/text

update_sublibrary line_drawer

update_sublibrary parse

update_sublibrary shader

update_sublibrary sprite

update_sublibrary systems

update_sublibrary texture

update_sublibrary time

update_sublibrary viewport

# plugins
update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_FILES \
	-n \
	src/plugins/opengl \
	-r \
	src/plugins/opengl/context \
	src/plugins/opengl/convert \
	src/plugins/opengl/fbo \
	src/plugins/opengl/glew \
	src/plugins/opengl/glsl \
	src/plugins/opengl/src \
	src/plugins/opengl/texture \
	src/plugins/opengl/vf

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_WIN32_FILES \
	src/plugins/opengl/wgl \
	src/plugins/opengl/windows

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_X11_FILES \
	src/plugins/opengl/glx \
	src/plugins/opengl/x11

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_XF86VMODE_FILES \
	src/plugins/opengl/xf86vmode

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_XRANDR_FILES \
	src/plugins/opengl/xrandr

update_plugin audio_null

update_plugin devil

update_plugin d3d9

update_plugin dinput

update_plugin freetype

update_plugin iconv

update_plugin libpng

update_plugin md3

update_plugin openal

update_plugin vorbis

update_plugin wave

update_plugin winconv

update_plugin x11input
