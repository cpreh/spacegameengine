#!/bin/sh

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" src/include || exit

check_src() {
	"${INCLUDE_BINARY}" src/"$1"/include || exit
}

check_src cegui
check_src config
check_src console
check_src font/bitmap
check_src font/text
check_src image
check_src input
check_src line_drawer
check_src model/md3
check_src model/obj
check_src opencl
check_src parse
check_src plugin
check_src projectile
check_src renderer
check_src systems
check_src viewport

for i in src/plugins/* ; do
	if [[ -d "${i}" ]] ; then
		"${INCLUDE_BINARY}" "$i"/include || exit
	fi
done
