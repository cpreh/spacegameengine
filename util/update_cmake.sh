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
	include/sge/timer

update_cmake_file \
	src/CMakeLists.txt \
	SGE_CORE_SRC_FILES \
	-n \
	src

function update_sublibrary()
{
	local sublibrary="$1"

	local upperpath="${sublibrary^^}"

	update_cmake_file \
		src/"${sublibrary}"/CMakeLists.txt \
		SGE_"${upperpath////}"_FILES \
		$2 \
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
update_sublibrary audio

update_sublibrary camera

update_sublibrary cegui

update_sublibrary charconv

update_sublibrary config

update_sublibrary console

update_sublibrary font -n

update_sublibrary font/bitmap

update_sublibrary font/text

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

update_cmake_file \
	src/renderer/CMakeLists.txt \
	SGE_RENDERER_FILES \
	-n \
	include/sge/renderer \
	-r \
	include/sge/renderer/caps \
	include/sge/renderer/glsl \
	include/sge/renderer/index \
	include/sge/renderer/light \
	include/sge/renderer/lock_flags \
	include/sge/renderer/projection \
	include/sge/renderer/state \
	include/sge/renderer/texture \
	include/sge/renderer/vf \
	-n \
	src/renderer \
	-r \
	src/renderer/caps \
	src/renderer/glsl \
	src/renderer/include \
	src/renderer/index \
	src/renderer/light \
	src/renderer/lock_flags \
	src/renderer/projection \
	src/renderer/state \
	src/renderer/texture \
	src/renderer/vf \

update_sublibrary renderer/opengl

update_sublibrary shader

update_sublibrary sprite

update_sublibrary systems

update_sublibrary texture

update_sublibrary viewport

update_sublibrary window

function opengl_inc_src() {
	echo "src/plugins/opengl/include/sge/opengl/$1" "src/plugins/opengl/src/$1"
}

# plugins
update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_BASE_FILES \
	-n src/plugins/opengl/src \
	-r \
	$(opengl_inc_src buffer) \
	$(opengl_inc_src context) \
	$(opengl_inc_src convert) \
	$(opengl_inc_src fbo) \
	$(opengl_inc_src glew) \
	$(opengl_inc_src glsl) \
	$(opengl_inc_src light) \
	$(opengl_inc_src state) \
	$(opengl_inc_src texture) \
	$(opengl_inc_src vf)

# opengl
update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_WIN32_FILES \
	$(opengl_inc_src wgl) \
	$(opengl_inc_src windows)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_X11_FILES \
	$(opengl_inc_src glx) \
	$(opengl_inc_src x11)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_XF86VMODE_FILES \
	$(opengl_inc_src xf86vmode)

update_cmake_file \
	src/plugins/opengl/CMakeLists.txt \
	SGE_OPENGL_XRANDR_FILES \
	$(opengl_inc_src xrandr)

update_plugin audio_null

update_plugin devil

update_plugin d3d9

update_plugin dinput

update_plugin freetype

update_plugin iconv

update_plugin libpng

update_plugin openal

update_plugin vorbis

update_plugin wave

update_plugin winconv

update_plugin x11input
