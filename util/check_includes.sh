#!/bin/sh

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" src/include || exit

"${INCLUDE_BINARY}" src/plugins SGE_  | grep -v X11INPUT || exit

check_plugin() {
	"${INCLUDE_BINARY}" src/plugins/"$1"/include || exit
}

check_plugin x11input
