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
check_src plugin

"${INCLUDE_BINARY}" src/plugins SGE_  | grep -v X11INPUT || exit

check_plugin() {
	"${INCLUDE_BINARY}" src/plugins/"$1"/include || exit
}

check_plugin x11input
