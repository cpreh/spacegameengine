#!/bin/sh
update_cmake \
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
	|| exit
mv src/CMakeLists.txt.new src/CMakeLists.txt || exit

update_cmake \
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
	|| exit

mv src/CMakeLists.txt.new src/CMakeLists.txt || exit
