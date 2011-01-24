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
}

update_cmake_file \
	src/CMakeLists.txt \
	SGE_CORE_INCLUDE_FILES \
	-n \
	include/sge \
	-r \
	include/sge/audio \
	include/sge/charconv \
	include/sge/collision \
	include/sge/error \
	-n \
	include/sge/font \
	-r \
	include/sge/image \
	include/sge/image2d \
	include/sge/image3d \
	include/sge/input \
	include/sge/library \
	include/sge/log \
	include/sge/model \
	include/sge/plugin \
	include/sge/renderer \
	include/sge/window \

update_cmake_file \
	src/CMakeLists.txt \
	SGE_CORE_SRC_FILES \
	-n \
	src \
	-r \
	src/audio \
	src/charconv \
	src/collision \
	-n \
	src/font \
	-r \
	src/image \
	src/image2d \
	src/image3d \
	src/input \
	src/library \
	src/log \
	src/model \
	src/plugin \
	src/renderer \
	src/window \

function update_sublibrary()
{
	local sublibrary="$1"

	update_cmake_file \
		src/"${sublibrary}"/CMakeLists.txt \
		SGE_$(echo "${sublibrary}" | tr "[:lower:]" "[:upper:]")_FILES \
		include/sge/"${sublibrary}" \
		src/"${sublibrary}"
}

update_sublibrary camera

update_sublibrary config
